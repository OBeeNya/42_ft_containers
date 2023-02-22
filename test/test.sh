NAME=containers

CONT=("vector" "stack" "map" "set")

for cont in ${CONT[@]}; do

	c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 "$cont"_test.cpp -DLIB=ft -o $NAME

	start1=$(date +%s.%N)

	./$NAME > logs/"$cont"_ft.txt

	end1=$(date +%s.%N)
	time1=$(echo "scale=9; $end1 - $start1" | bc)

	c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 "$cont"_test.cpp -DLIB=std -o $NAME

	start2=$(date +%s.%N)

	./$NAME > logs/"$cont"_std.txt

	end2=$(date +%s.%N)
	time2=$(echo "scale=9; $end2 - $start2" | bc)
	comp=$(echo "scale=2; $time2 / $time1" | bc)
	echo ft::"$cont" is $comp x slower than std::"$cont"

	diff logs/"$cont"_ft.txt logs/"$cont"_std.txt > logs/"$cont"_diff.txt

	if [ -s logs/"$cont"_diff.txt ]; then
		echo "differences in" $cont "implementations"
	else
		echo $cont "implementation is ok"
	fi

	echo

done

rm ./$NAME
