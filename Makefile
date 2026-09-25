all: tct nasa pdt

tct: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall TimeCodeTests.cpp TimeCode.cpp -o tct

tct-debug: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall -g TimeCodeTests.cpp TimeCode.cpp -o tct-debug

nasa: NasaLaunchAnalysis.cpp TimeCode.cpp TimeCode.h
	g++ -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa

nasa-debug: NasaLaunchAnalysis.cpp TimeCode.cpp TimeCode.h
	g++ -Wall -g TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa-debug

pdt: PaintDryTimer.cpp TimeCode.cpp TimeCode.h
	g++ -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt

pdt-debug: PaintDryTimer.cpp TimeCode.cpp TimeCode.h
	g++ -Wall -g TimeCode.cpp PaintDryTimer.cpp -o pdt-debug

clean:
	rm -f tct tct-debug nasa nasa-debug pdt pdt-debug