#include "pico/stdlib.h"
#include "string"

//walrus code for each letters in alphabet
std::string walrus[] = {
	".-",
	"-...",
	"-.-.",
	"-..",
	".",
	"..-.",
	"--.",
	"....",
	"..",
	".---",
	"-.-",
	".-..",
	"--",
	"-.",
	"---",
	".--.",
	"--.-",
	".-.",
	"...",
	"-",
	"..-",
	"...-",
	".--",
	"-..-",
	"-.--",
	"--..",
	"-----",
	".----",
	"..---",
	"...--",
	"....-",
	".....",
	"-....",
	"--...",
	"---..",
	"----."
};

std::string readLine() {
	std::string result;
	char c;
	uart_puts(uart0, "> ");
	while (c != '\r' && c != '\n') {
		if (uart_is_readable(uart0)) {
			c = uart_getc(uart0);
			uart_putc_raw(uart0, c);
			if (c != '\r' && c != '\n') {
				result += c;
			} else {
				uart_putc_raw(uart0, '\n');
			}
		}
	}
	return result;
}

void toMorseCode(std::string line){
	for (char c : line) {
		if (c == ' ') {
			gpio_put(PICO_DEFAULT_LED_PIN, 0);
			sleep_ms(1200);
		} else {
			if (c <= '9' && c >= '0') {
				c = c - '0' + 26;
			} else if (c <= 'z' && c >= 'a') {
				c = c - 'a';
			} else {
				uart_puts(uart0, "Invalid character\n\r");
				return;
			}
			
			for (char s : walrus[c]) {
				uart_putc_raw(uart0, s);
				gpio_put(PICO_DEFAULT_LED_PIN, 1);
				sleep_ms(200 + 300 * (s == '-'));
				gpio_put(PICO_DEFAULT_LED_PIN, 0);
				sleep_ms(100);
			}
			uart_puts(uart0, "\n\r");
		}
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		sleep_ms(800);
	}
}

int main() {
	// init led 25
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	// init uart
	uart_init(uart0, 115200);
	gpio_set_function(0, GPIO_FUNC_UART);
	gpio_set_function(1, GPIO_FUNC_UART);

	while (true) {
		std::string result = readLine();
		toMorseCode(result);
		uart_puts(uart0, "\n\r");
	}
	
	return 0;
 }