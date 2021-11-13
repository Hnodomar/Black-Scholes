reset
set title "Delta Hedging Profit and Loss" textcolor rgb "white"
set border lw 1 lc rgb "white"
set ylabel "Frequency" textcolor rgb "white"
set xlabel "Profit and Loss (£)" textcolor rgb "white"
num_bins = 20
stats 'histogram.dat' using 1 nooutput
bin_width = (STATS_max - STATS_min) / num_bins
#bin(x) = width * (floor((x - STATS_min) / width) + 0.5) + STATS_min
set boxwidth bin_width
bin(x, width) = width * floor(x / width)
plot 'histogram.dat' using (bin($1, bin_width)):(1.0) smooth freq with boxes notitle
