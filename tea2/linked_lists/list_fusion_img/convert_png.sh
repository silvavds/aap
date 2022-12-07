#!/bin/bash

for filename in ./dots/*.dot; do
    
	#echo "$filename"
	echo $(basename $filename .dot)
	
	$(dot ./dots/$(basename $filename) -T png -o ./images/$(basename $filename .dot).png)
	    
done
