#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate greatest common divisor (GCD) of two numbers
unsigned long gcd(unsigned long a, unsigned long b) {
    
  //Body of the function. This function should be implemented recursively
  // Use Euclidean algorithm; repeat subtracting from larger of two favlues until end up with GCD
  // GCD doesn't change when subtracting smaller value from larger value
  if (a > b) {
    return gcd(a - b, b);
  }
  else if (a < b) {
    return gcd(a, b - a);
  }

  if (a == 0) {
    return b;
  }
  else if (b == 0) {
    return a;
  }

  if (a == b) {
    return a;
  }

  return 0;
}

// Function to calculate modulo inverse using extended Euclidean algorithm
unsigned long modInverse(unsigned long a, unsigned long m) {
  // Extended euclidean algorithm, ax + my = gcd(a,m)
  // Since a and m are coprime, gcd(a, m) = 1
  // Algorithm simplifies to ax + my = 1 
  // Then take mod M on both sides
  // ax + my = 1 (mod M)
  // x is what we will return since it represents the modular inverse of a modulo m, ignore y
  // ax = 1 (mod M), where x is the multiplicative inverse of a

  //Body of the function
  int result = 0;
  for (int i = 0; i < m; i++) {
    if (a * i % m == 1) {
      result = i;
      return result;
    }
  }

  return result;
}

// Function to generate keys for RSA encryption
void generateKeys(unsigned long p, unsigned long q, unsigned long *n, unsigned long *e, unsigned long *d) {
  unsigned long phi;
  int isEQualified = 0;  // e must be less than phi and coprime with phi to be qualified

  //Body of the function
  *n = p*q;
  phi = (p - 1)*(q - 1);
  while (isEQualified == 0) {
    *e = rand() % (phi + 1);  // Choose a random int between 1 and phi, exclusive

    if (gcd(*e, phi) == 1) {
      isEQualified = 1;
    }
  }

  // Define d as modular multiplicative inverse of e mod phi  
  //printf("\n e = %d, phi = %d\n", *e, phi);
  //*e = 7;  // TEST
  *d = modInverse(*e, phi);

  // Discard phi, p, and q
  (void) phi, p, q;
}

// Function to encrypt plaintext using RSA
unsigned long long encrypt(unsigned long plaintext, unsigned long e, unsigned long n) {

  //Body of the function
  //printf("plaintext = %lu, e = %lu, n = %lu\n", plaintext, e, n);
  unsigned long long result = (unsigned long long) pow(plaintext, e);
  //printf("%llu\n", result);
  return result % n;
}

// Function to decrypt ciphertext using RSA
unsigned long long decrypt(unsigned long long ciphertext, unsigned long d, unsigned long n) {
    
  //Body of the function
  //printf("ciphertext = %llu, d = %lu, n = %lu\n", ciphertext, d, n);
  unsigned long long result = (unsigned long long) pow(ciphertext, d);
  //printf("%llu\n", result);
  return result % n;
}

unsigned long main() {
    unsigned long p;  // prime number, try  3, 5, 7, 11, 13, ...
    unsigned long q; // prime number, try  3, 5, 7, 11, 13, ...
    
    unsigned long n, e, d;
  
    printf("\nEnter p and q: ");
    scanf("%lu %lu", &p, &q);
    // Generate RSA keys
    generateKeys(p, q, &n, &e, &d);

    printf("Public key (e, n): (%lu, %lu)\n", e, n);
    printf("Private key (d, n): (%lu, %lu)\n\n", d, n);

// Encrypt and decrypt a sample plaintext, which we assume is given as an integer value

    unsigned long plaintext;
    printf("Enter an integer between 0 and n-1 as plain text to be encrypted: ");
    scanf("%lu", &plaintext);
    printf("Original plaintext: %lu\n", plaintext);
    unsigned long long ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %llu\n", ciphertext);
    unsigned long long decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %llu\n\n", decrypted);

   
    return 0;
}
