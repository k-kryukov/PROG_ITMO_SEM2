This lab is an application which sends HTTP-requests to Central Bank of Russia 
and asks for current exchange rates.
Every ten seconds requests are sent, median and average values are counted and result is written to output file.
To compile code you should firstly include "libCurl" as a static library.