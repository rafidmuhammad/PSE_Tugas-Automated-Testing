#include <fsm.h>
#include <unity.h>
#include <define.h>

void test_function_fsm_init(void)
{
    int edge, led, debounce;
    fsm_init(&edge, &debounce, &led);
    TEST_ASSERT_EQUAL(StateEdge1, edge);
    TEST_ASSERT_EQUAL(StateDebounce1, debounce);
    TEST_ASSERT_EQUAL(First, led);
}

void test_function_fsm_edge_detector(void)
{
    int output, edge, led, debounce;
    int first_input = 1;
    int second_input = 0;
    fsm_init(&edge, &debounce, &led);
    edgedetector(&edge, &first_input, &output);
    TEST_ASSERT_EQUAL(StateEdge2, edge);
    TEST_ASSERT_EQUAL(1, output);
    edgedetector(&edge, &second_input, &output);
    TEST_ASSERT_EQUAL(StateEdge1, edge);
    TEST_ASSERT_EQUAL(0, output);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_function_fsm_init);
    RUN_TEST(test_function_fsm_edge_detector);
    UNITY_END();
    return 0;
}
