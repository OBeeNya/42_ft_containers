CONT=("vector" "stack" "map" "set")

for cont in ${CONT[@]}; do
	rm "$cont"_ft.txt
	rm "$cont"_std.txt
	rm "$cont"_diff.txt
done
