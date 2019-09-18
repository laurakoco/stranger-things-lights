
# Laura Kocubinski
# Tyler Seubert

#include <FastLED.h>

// user definitions

#define data_pin 6  // define the data pin connected to the data input DIN of the LED strip
#define num_leds 50 // define the number of LEDs in the strip
String my_words[] = {"help","run","imhere","upsidedown","demogorgon"}; // define words to spell with LEDs

// RGB color order
#define color_order RGB

// CRGB object for storing LED data
CRGB leds[num_leds]; 

void setup(){
  
  // set up FastLED
  FastLED.addLeds<WS2811, data_pin, color_order>(leds, num_leds);
}

void loop(){

  // blink leds orange and purple
  blink();
  blink();

  // turn off leds without delay
  turn_off_all_leds();
   
  // scroll forward and backwards 
  scroll();
  reverse_scroll(); 

   // print randomly choosen word with LEDs
   light_word( generate_word() );
}

void blink(){

  int my_delay = 2000;

  for(int i = 0; i < num_leds; i++){

    if(i % 2 == 0){
        leds[i] = CRGB::OrangeRed;
        FastLED.show();
        }

    if(i % 2 == 1){
        leds[i] = CRGB::Purple;
        FastLED.show();
        }
  }

  delay(my_delay);

  for(int i = 0; i < num_leds; i++){
    if(i % 2 == 0){
        leds[i] = CRGB::Purple;
        FastLED.show();
    }

    if(i % 2 == 1){
        leds[i] = CRGB::OrangeRed;
        FastLED.show();
        }
  }

  delay(my_delay);
}

void turn_off_all_leds(){
  
  for(int i=0; i < num_leds; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

// scroll forward through led[0] to led[num_leds-1]
void scroll(){

  int my_delay = 50;

  for(int i=0; i < num_leds; i++){
    light_led(i, my_delay);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

// scroll backward through led[num_leds-1] to led[0]
void reverse_scroll(){
  
  int my_delay = 50;
  
  for(int i = num_leds-1; i >= 1; i--){
    light_led(i, my_delay);
    leds[i] = CRGB::Black;
    FastLED.show();
   }
} 

// randomly choose word from my_words array
String generate_word() {   
  
   // calculate number of elements in array by finding bits of each element, since each element is of same type
   int arr_size = sizeof(my_words) / sizeof(my_words[0]);
   
   // generate random number
   int ran_number = random(0 , arr_size);
   
   // find word in my_words[]
   for(int i = 0; i < arr_size; i++){
      if(i == ran_number){
          return my_words[i];
        }  
   } 
}

// convert char in word to led number
void light_word(String my_word){ 
  
  int my_delay = 2000;
  int alphabet = 26;
  
  // map ascii character decimal value to led number by subtracting a constant 
  int ascii_offset = 97 - (((num_leds - alphabet)/2 - 1) );
 
   for(int i = 0; i < my_word.length(); i++) {

    int led_number = my_word[i] - ascii_offset;

    // light led with color
    light_led(led_number, my_delay);

    // turn off all leds
    turn_off_all_leds();
    }
}

// lights the led purple or orange
void light_led(int led_number, int my_delay){

    if(led_number % 2 == 0){
        leds[led_number] = CRGB::OrangeRed;
        FastLED.show();
        delay(my_delay);
        }

    if(led_number % 2 == 1){
        leds[led_number] = CRGB::Purple;
        FastLED.show();
        delay(my_delay);
        }
}
