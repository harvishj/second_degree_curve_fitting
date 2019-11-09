all:
	gcc main.c
	./a.out
	gnuplot --persist -e "plot 'gnuplot.txt' with lines, 'datapoints.txt' smooth unique with linespoints set title 'Main'"
compile: