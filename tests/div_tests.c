#include "s21_tests.h"
#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3
void tests_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_eq(check.bits[0], result.bits[0]);
    ck_assert_int_eq(check.bits[1], result.bits[1]);
    ck_assert_int_eq(check.bits[2], result.bits[2]);
    ck_assert_int_eq(check.bits[3], result.bits[3]);
    ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void tests_div_fail1(s21_decimal decimal1, s21_decimal decimal2,
                     int code_check) {
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);
    ck_assert_int_eq(code, code_check);
}

void tests_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                     s21_decimal decimal_check, int code_check) {
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_eq(code, code_check);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Тесты на некорректные данные (ручные)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */
//
START_TEST(tests_div_fail_manual1) {
        // 792281625.14264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
        int code = s21_div(decimal1, decimal2, NULL);

        ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(tests_div_fail_manual2) {
        // степень 154 (показатель степени должен быть от 0 до 28)
        // биты 0-15 не нули
        // биты 24-30 не нули
        s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
        s21_decimal result;
        int code = s21_div(decimal1, decimal2, &result);

        ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual9) {
    // Просто все единицы
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual10) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual11) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual12) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual13) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual14) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual15) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual16) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_div_fail_manual17) {
    // Просто все единицы
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    s21_decimal result;
    int code = s21_div(decimal1, decimal2, &result);

    ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Тесты на все типы данных (ручные)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */




START_TEST(tests_div_manual5) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 7.9228162514264337593543950335
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
        // 10000000000000000000000000000
        s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

        tests_div(decimal1, decimal2, check);
}

START_TEST(tests_div_manual6) {
        // 7.9228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
        // 79228162514264337593543950335
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 0.0000000000000000000000000001
        s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

        tests_div(decimal1, decimal2, check);
}


START_TEST(tests_div_manual14) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // -0
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div_manual15) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 0.0000000000000000000000000001
        s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
        // overflow
        int code_check = TEST_ARITHMETIC_BIG;

        tests_div_fail1(decimal1, decimal2, code_check);
}




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(tests_div1) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 79228162514264337593543950335
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div2) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // -79228162514264337593543950335
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
        // -1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div3) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 7922816251426433759354395033.5
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
        // 10
        s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div4) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // -7922816251426433759354395033.5
        s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
        // -10
        s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div5) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 79228162514264337593543950334
        s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // 1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div6) {
        // 79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
        // -79228162514264337593543950334
        s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
        // -1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

        tests_div(decimal1, decimal2, decimal_check);
}


START_TEST(tests_div24) {
        // -79228162514264337593543950335
        s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
        // -0.001
        s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
        // overflow
        int code_check = TEST_ARITHMETIC_BIG;

        tests_div_fail1(decimal1, decimal2, code_check);
}


START_TEST(tests_div27) {
        // 2147483648
        s21_decimal decimal1 = {{0x80000000, 0x0, 0x0, 0x0}};
        // 2147483648
        s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
        // 1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div28) {
        // 2147483648
        s21_decimal decimal1 = {{0x80000000, 0x0, 0x0, 0x0}};
        // -2147483648
        s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
        // -1
        s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div29) {
        // 2147483648
        s21_decimal decimal1 = {{0x80000000, 0x0, 0x0, 0x0}};
        // -0.0000000000000000000000000000
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}




START_TEST(tests_div45) {
        // -0.0000000000000000000000000001
        s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x801C0000}};
        // -0
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div46) {
        // -0.0000000000000000000000000001
        s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x801C0000}};
        // 0
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div47) {
        // -0.0000000000000000000000000001
        s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x801C0000}};
        // -0.0000000000000000000000000000
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}


START_TEST(tests_div55) {
        // -0.019
        s21_decimal decimal1 = {{0x13, 0x0, 0x0, 0x80030000}};
        // 0.0000000000000000000000000001
        s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
        // -190000000000000000000000000
        s21_decimal decimal_check = {{0x7E000000, 0xA37C185D, 0x9D2A10, 0x80000000}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div56) {
        // -0.019
        s21_decimal decimal1 = {{0x13, 0x0, 0x0, 0x80030000}};
        // -0.0000000000000000000000000001
        s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
        // 190000000000000000000000000
        s21_decimal decimal_check = {{0x7E000000, 0xA37C185D, 0x9D2A10, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}



START_TEST(tests_div61) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 2
        s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}


START_TEST(tests_div63) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 1.9999999999999999999999999000
        s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div65) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 1.9999999999999999999999999999
        s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}

START_TEST(tests_div67) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 1.0000000000000000000000000001
        s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}


START_TEST(tests_div69) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 0.0000000000000000000000000001
        s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}


START_TEST(tests_div71) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 0.0000000000000000000000000010
        s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
        // 0
        s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

        tests_div(decimal1, decimal2, decimal_check);
}



START_TEST(tests_div73) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // -0
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div74) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 0
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div75) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // -0.0000000000000000000000000000
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_div76) {
        // 0
        s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
        // 0.0000000000000000000000000000
        s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
        // division by zero
        int code_check = TEST_ARITHMETIC_ZERO_DIV;

        tests_div_fail1(decimal1, decimal2, code_check);
}

Suite *div_suite() {
    Suite *s = suite_create("\033[45m-=S21_suite_div_mini=-\033[0m");
    TCase *tc_core = tcase_create("case_div");

    tcase_add_test(tc_core, tests_div_fail_manual1);
    tcase_add_test(tc_core, tests_div_fail_manual2);
    tcase_add_test(tc_core, tests_div_fail_manual3);
    tcase_add_test(tc_core, tests_div_fail_manual4);
    tcase_add_test(tc_core, tests_div_fail_manual5);
    tcase_add_test(tc_core, tests_div_fail_manual6);
    tcase_add_test(tc_core, tests_div_fail_manual7);
    tcase_add_test(tc_core, tests_div_fail_manual8);
    tcase_add_test(tc_core, tests_div_fail_manual9);
    tcase_add_test(tc_core, tests_div_fail_manual10);
    tcase_add_test(tc_core, tests_div_fail_manual11);
    tcase_add_test(tc_core, tests_div_fail_manual12);
    tcase_add_test(tc_core, tests_div_fail_manual13);
    tcase_add_test(tc_core, tests_div_fail_manual14);
    tcase_add_test(tc_core, tests_div_fail_manual15);
    tcase_add_test(tc_core, tests_div_fail_manual16);
    tcase_add_test(tc_core, tests_div_fail_manual17);





    tcase_add_test(tc_core, tests_div_manual5);
    tcase_add_test(tc_core, tests_div_manual6);

    tcase_add_test(tc_core, tests_div_manual14);
    tcase_add_test(tc_core, tests_div_manual15);


    ////
    tcase_add_test(tc_core, tests_div1);
    tcase_add_test(tc_core, tests_div2);
    tcase_add_test(tc_core, tests_div3);
    tcase_add_test(tc_core, tests_div4);
    tcase_add_test(tc_core, tests_div5);
    tcase_add_test(tc_core, tests_div6);
    tcase_add_test(tc_core, tests_div24);
    tcase_add_test(tc_core, tests_div27);
    tcase_add_test(tc_core, tests_div28);
    tcase_add_test(tc_core, tests_div29);
    tcase_add_test(tc_core, tests_div45);
    tcase_add_test(tc_core, tests_div46);
    tcase_add_test(tc_core, tests_div47);
    tcase_add_test(tc_core, tests_div55);
    tcase_add_test(tc_core, tests_div56);

    tcase_add_test(tc_core, tests_div61);
    tcase_add_test(tc_core, tests_div63);

    tcase_add_test(tc_core, tests_div65);

    tcase_add_test(tc_core, tests_div67);
    tcase_add_test(tc_core, tests_div69);
    tcase_add_test(tc_core, tests_div71);
    tcase_add_test(tc_core, tests_div73);
    tcase_add_test(tc_core, tests_div74);
    tcase_add_test(tc_core, tests_div75);
    tcase_add_test(tc_core, tests_div76);
    suite_add_tcase(s, tc_core);
    return s;
}
