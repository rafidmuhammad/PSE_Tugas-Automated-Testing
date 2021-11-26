#include <define.h>
#include <fsm.h>

void fsm_init(int *state_edge, int *state_debounce, int *state_running)
{
    *state_edge = StateEdge1;
    *state_debounce = StateDebounce1;
    *state_running = First;
}

/**
 * @brief unutk melakukan pendeteksian rising edge
 *
 * @param state dua state untuk handling edge detector
 * @param input input untuk suatu tombol
 * @param output akan mengeluarkan satu ketika transisi nol ke satu
 */
void edgedetector(int *state, int *input, int *output)
{
    switch (*state)
    {
    case StateEdge1:
    {
        if (*input == 1)
        {
            *state = StateEdge2;
            *output = 1;
        }
        break;
    }
    case StateEdge2:
    {
        if (*input == 0)
        {
            *state = StateEdge1;
            *output = 0;
        }
        break;
    }
    default:
        break;
    }
}

/**
 * @brief untuk debouncing handler
 *
 * @param state menggambarkan keadaan state untuk debouncing
 *              state 1 berpindah ke state dua jika terdapat input 1,
 *              state 2 akan berpindah ketika counter sudah habis,
 *              state 3 akan berpindah ketika input menjadi 0,
 *              state 4 akan berpindah jika counter habis
 * @param input akan menerima input dari edge detector. input berupa 0 atau 1
 * @param output akan terdapat pada setiap state dan transisi state
 */

void debouncing(int *state, int *input, int *output)
{
    int counter;
    switch (*state)
    {
    case StateDebounce1:
        if (*input == 1)
        {
            *state = StateDebounce2;
            counter = 0;
            *output = 1;
        }
        else
        {
            *output = 0;
        }
        break;
    case StateDebounce2:
        if (counter < 100)
        {
            counter++;
            *output = 1;
        }
        else
        {
            *state = StateDebounce3;
        }
        break;
    case StateDebounce3:
        if (*input == 0)
        {
            *state = StateDebounce4;
            counter = 0;
            *output = 0;
        }
        else
        {
            *output = 1;
        }

        break;
    case StateDebounce4:
        if (counter < 100)
        {
            counter++;
            *output = 0;
        }
        else
        {
            *state = StateDebounce1;
        }
        break;
    default:
        break;
    }
}

/**
 * @brief untuk menggambarkan perubahan running led
 *
 * @param inputR input untuk tombol kanan
 * @param inputL input untuk tombol kiri
 * @param state  state akan berubah setiap terdapat input 1 dari
 *               tombol kiri ataupun kanan
 * @param output mengeluarkan integer yang nantinya akan diubah menjadi bit
 *               sehingga bisa dipakai untuk akses register arduino
 */

void running(int *inputR, int *inputL, int *state, int *output)
{

    // perubahan state saat tombol kanan ditekan
    switch (*state)
    {
    case First:
        if (*inputR == 1)
        {
            *state = Second;
        }
        break;
    case Second:
        if (*inputR == 1)
        {
            *state = Third;
        }
        break;
    case Third:
        if (*inputR == 1)
        {
            *state = Fourth;
        }
        break;
    case Fourth:
        if (*inputR == 1)
        {
            *state = First;
        }
        break;
    default:
        break;
    }

    // perubahan state saat tombol kiri ditekan
    switch (*state)
    {
    case First:
        if (*inputL == 1)
        {
            *state = Fourth;
        }
        break;
    case Second:
        if (*inputL == 1)
        {
            *state = First;
        }
        break;
    case Third:
        if (*inputL == 1)
        {
            *state = Second;
        }
        break;
    case Fourth:
        if (*inputL == 1)
        {
            *state = Third;
        }
        break;

    default:
        break;
    }

    // output state akan diubah menjadi bit
    switch (*state)
    {
    case First:
        *output = 1;
        break;
    case Second:
        *output = 2;
        break;
    case Third:
        *output = 3;
        break;
    case Fourth:
        *output = 4;
        break;
    default:
        break;
    }
}
