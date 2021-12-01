#include <fsm.h>
#include <unity.h>
#include <define.h>

void test_function_fsm_init(void)
{
    int edge, led, debounce;
    fsm_init(&edge, &debounce);
    TEST_ASSERT_EQUAL(StateEdge1, edge);
    TEST_ASSERT_EQUAL(StateDebounce1, debounce);
}

void test_function_fsm_edge_detector(void)
{
    int output, edge, led, debounce;
    int first_input = 1;
    int second_input = 0;
    fsm_init(&edge, &debounce);
    //
    edgedetector(&edge, &first_input, &output);
    TEST_ASSERT_EQUAL(StateEdge2, edge);
    TEST_ASSERT_EQUAL(1, output);
    //
    edgedetector(&edge, &second_input, &output);
    TEST_ASSERT_EQUAL(StateEdge1, edge);
    TEST_ASSERT_EQUAL(0, output);
}

void test_function_fsm_debouncing(void)
{
    int output, edge, led, debounce;
    int first_input = 1;
    int second_input = 0;

    // STATE PERTAMA
    // kasus input == 0
    fsm_init(&edge, &debounce);
    debouncing(&debounce, &second_input, &output);
    TEST_ASSERT_EQUAL(StateDebounce1, debounce);
    TEST_ASSERT_EQUAL(0, output);
    //  kasus input == 1
    fsm_init(&edge, &debounce);
    debouncing(&debounce, &first_input, &output);
    TEST_ASSERT_EQUAL(StateDebounce2, debounce);
    TEST_ASSERT_EQUAL(1, output);

    // STATE KEDUA
    for (int i = 0; i < 100; i++)
    {
        debouncing(&debounce, &first_input, &output);
        TEST_ASSERT_EQUAL(1, output);
    }
    debouncing(&debounce, &first_input, &output);
    TEST_ASSERT_EQUAL(StateDebounce3, debounce);

    // STATE KETIGA
    // kasus else
    TEST_ASSERT_EQUAL(1, output);
    // kasus if
    debouncing(&debounce, &second_input, &output);
    TEST_ASSERT_EQUAL(StateDebounce4, debounce);
    TEST_ASSERT_EQUAL(0, output);

    // STATE KEEMPAT
    for (int i = 0; i < 100; i++)
    {
        debouncing(&debounce, &first_input, &output);
        TEST_ASSERT_EQUAL(0, output);
    }
    debouncing(&debounce, &first_input, &output);
    TEST_ASSERT_EQUAL(StateDebounce1, debounce);
}

void test_function_fsm_running_led(void)
{
    int output = 1, edge, debounce;
    int input_RIGHT_on = 1;
    int input_RIGHT_off = 0;
    int input_LEFT_on = 1;
    int input_LEFT_off = 0;
    int led = First;

    fsm_init(&edge, &debounce);
    // arah kanan
    running(&input_RIGHT_on, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(1, output);
    TEST_ASSERT_EQUAL(dummyFirst, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(2, output);
    TEST_ASSERT_EQUAL(Second, led);

    running(&input_RIGHT_on, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(2, output);
    TEST_ASSERT_EQUAL(dummySecond, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(3, output);
    TEST_ASSERT_EQUAL(Third, led);

    running(&input_RIGHT_on, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(3, output);
    TEST_ASSERT_EQUAL(dummyThird, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(4, output);
    TEST_ASSERT_EQUAL(Fourth, led);

    running(&input_RIGHT_on, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(4, output);
    TEST_ASSERT_EQUAL(dummyFourth, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(1, output);
    TEST_ASSERT_EQUAL(First, led);

    // kekiri
    running(&input_RIGHT_off, &input_LEFT_on, &led, &output);
    TEST_ASSERT_EQUAL(1, output);
    TEST_ASSERT_EQUAL(dummyFourthLeft, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(4, output);
    TEST_ASSERT_EQUAL(Fourth, led);

    running(&input_RIGHT_off, &input_LEFT_on, &led, &output);
    TEST_ASSERT_EQUAL(4, output);
    TEST_ASSERT_EQUAL(dummyThirdL, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(3, output);
    TEST_ASSERT_EQUAL(Third, led);

    running(&input_RIGHT_off, &input_LEFT_on, &led, &output);
    TEST_ASSERT_EQUAL(3, output);
    TEST_ASSERT_EQUAL(dummySecondL, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(2, output);
    TEST_ASSERT_EQUAL(Second, led);

    running(&input_RIGHT_off, &input_LEFT_on, &led, &output);
    TEST_ASSERT_EQUAL(2, output);
    TEST_ASSERT_EQUAL(dummyFirstL, led);
    running(&input_RIGHT_off, &input_LEFT_off, &led, &output);
    TEST_ASSERT_EQUAL(1, output);
    TEST_ASSERT_EQUAL(First, led);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_function_fsm_init);
    RUN_TEST(test_function_fsm_edge_detector);
    RUN_TEST(test_function_fsm_debouncing);
    RUN_TEST(test_function_fsm_running_led);
    UNITY_END();
    return 0;
}
