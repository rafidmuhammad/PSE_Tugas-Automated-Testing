#include <Arduino.h>
#include <fsm.h>
#include <define.h>

#define t1_load 0
#define t1_comp 6250

int StateEdge_kanan, StateEdge_kiri, StateDebouncing_kanan, StateDebouncing_kiri, StateLED_kanan, StateLED_kiri;
int input_kanan, input_kiri;
int input_edge_kanan, input_edge_kiri;
int input_running_kanan, input_running_kiri;
int output_angka;

void setup()
{
  // put your setup code here, to run once:

  fsm_init(&StateEdge_kanan, &StateDebouncing_kanan, &StateLED_kanan);
  fsm_init(&StateEdge_kiri, &StateDebouncing_kiri, &StateLED_kiri);
  // led
  DDRD = B00001111;
  PORTD = 0X00;

  // button
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  TCCR1A = 0;
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  // setup timer dengan compare match prescaler 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
  // Counter
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  // enabling output compare interrupt
  TIMSK1 = (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{

  if (digitalRead(6) == LOW)
  {
    input_kanan = 1;
  }
  else
  {
    input_kanan = 0;
  }

  if (digitalRead(7) == 0)
  {
    input_kiri = 1;
  }
  else
  {
    input_kiri = 0;
  }

  debouncing(&StateDebouncing_kanan, &input_kanan, &input_edge_kanan);
  debouncing(&StateDebouncing_kiri, &input_kiri, &input_edge_kiri);
  edgedetector(&StateEdge_kanan, &input_edge_kanan, &input_running_kanan);
  edgedetector(&StateEdge_kiri, &input_edge_kiri, &input_running_kiri);
  running(&input_running_kanan, &input_running_kiri, &StateLED_kanan, &output_angka);
}

void loop()
{
  // put your main code here, to run repeatedly:
}