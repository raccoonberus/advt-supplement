TARGET=advt_supplement

leak-check:
	cmake --build ./cmake-build-debug --target ${TARGET} -- -j 2
	valgrind --log-file="leaks.log" --tool=memcheck ./cmake-build-debug/${TARGET} ./assets/V_20180709_121047.mp4