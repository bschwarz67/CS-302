midi_tester: midi_tester.o cs302-midi-base.o cs302-midi.o
	g++ -std=c++98 -Wall -Wextra -o midi_tester midi_tester.o cs302-midi-base.o cs302-midi.o
mconvert: mconvert.o cs302-midi-base.o cs302-midi.o
	g++ -std=c++98 -Wall -Wextra -o mconvert mconvert.o cs302-midi-base.o cs302-midi.o
mconvert.o: mconvert.cpp
	g++ -std=c++98 -Wall -Wextra -c mconvert.cpp
midi_tester.o: midi_tester.cpp
	g++ -std=c++98 -Wall -Wextra -c midi_tester.cpp
cs302-midi-base.o: cs302-midi-base.cpp
	g++ -std=c++98 -Wall -Wextra -c cs302-midi-base.cpp
cs302-midi.o: cs302-midi.cpp
	g++ -std=c++98 -Wall -Wextra -c cs302-midi.cpp
