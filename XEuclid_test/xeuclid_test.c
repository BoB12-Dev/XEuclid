#include <stdio.h> 
#include <openssl/bn.h>

// BIGNUM 출력 함수
void printBN(char* msg, BIGNUM* a)
{
    // BIGNUM을 16진수 문자열로 변환하여 출력
    char* number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str); // 할당된 메모리 해제
}

BIGNUM* XEuclid(BIGNUM* x, BIGNUM* y, const BIGNUM* a, const BIGNUM* b)
{
    // a가 0일 경우, x=0, y=1로 설정하고 최대공약수로 b를 반환
    if (BN_is_zero(a)) {
        BN_zero(x); // x = 0
        BN_one(y);  // y = 1
        return BN_dup(b); // b를 복제한 값을 gcd로 반환
    }

    // 임시 변수들을 생성
    BIGNUM* x1 = BN_new();
    BIGNUM* y1 = BN_new();
    BIGNUM* gcd = BN_new();

    // b를 a로 나눈 나머지를 구한다.
    BIGNUM* temp = BN_new();
    BN_mod(temp, b, a, BN_CTX_new());

    // 재귀적으로 XEuclid 함수를 호출하여 최대공약수(gcd)와 gcd의 계수 x1, y1을 계산한다.
    gcd = XEuclid(x1, y1, temp, a);

    // x = y1 - (b / a) * x1
    BN_div(temp, NULL, b, a, BN_CTX_new());
    BN_mul(temp, temp, x1, BN_CTX_new());
    BN_sub(x, y1, temp);

    // y = x1
    BN_copy(y, x1);

    // 메모리를 해제한다.
    BN_free(temp);
    BN_free(x1);
    BN_free(y1);

    return gcd;
}

int main(int argc, char* argv[])
{
    BIGNUM* a = BN_new();
    BIGNUM* b = BN_new();
    BIGNUM* x = BN_new();
    BIGNUM* y = BN_new();
    BIGNUM* gcd;

    if (argc != 3) {
        printf("usage: xeuclid num1 num2");
        return -1;
    }

    BN_dec2bn(&a, argv[1]);
    BN_dec2bn(&b, argv[2]);

    gcd = XEuclid(x, y, a, b);

    // 결과 출력
    printBN("(a, b) = ", gcd);                              // 최대공약수(gcd) 출력
    printBN("a = ", a);                                      // 첫 번째 입력 수 출력
    printBN("b = ", b);                                      // 두 번째 입력 수 출력
    printBN("x = ", x);                                      // 최대공약수(gcd)의 계수 x 출력
    printBN("y = ", y);                                      // 최대공약수(gcd)의 계수 y 출력
    printf("%s*(%s) + %s*(%s) = %s\n", BN_bn2dec(a), BN_bn2dec(x), BN_bn2dec(b), BN_bn2dec(y), BN_bn2dec(gcd)); // 확장 유클리드 알고리즘 결과 출력

    // 메모리를 해제한다.
    BN_free(a);
    BN_free(b);
    BN_free(x);
    BN_free(y);
    BN_free(gcd);

    return 0;
}

