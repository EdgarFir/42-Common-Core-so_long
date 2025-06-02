#!/bin/bash

ERRORS=0

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
LIGHT_BLUE="\033[1;34m"
CIANE='\033[36m'

# Map errors
FILE_NOT_EXIST="File does not exist." # Tested
FILE_EXT_ERR="Non compatible map extension." # Tested
MAP_CHR_ERR="Map must have 1 exit, 1 start and at least 1 collectable." # Tested
MAP_INV_CHR_ERR="Map has an invalid character." # Tested
MAP_WALL_ERR="Map not surronded by walls." # Tested
MAP_SIZE_ERR="File .ber must have at least 3 lines." # Tested
MAP_COLLECT_ERR="Invalid map. Collectables not reachable." # Tested
MAP_EXIT_ERR="Invalid map. Exit not reachable." # Tested
MAP_RECT_ERR="Map is not a rectangule."

run_test_errors()
{
	FILE=$1
	TEST_RES_DIR=$2

	echo -e "$3 - ${LIGHT_BLUE}Testing map: ${YELLOW}${FILE}${NC}"
	valgrind --leak-check=full -s --show-leak-kinds=all ./so_long ${FILE} > ${TEST_RES_DIR} 2>&1
	LEAKS_RESULT=$(cat ${TEST_RES_DIR} | grep "All heap blocks were freed -- no leaks are possible")
	ERROR_OUTPUT=$(cat ${TEST_RES_DIR} | grep $4)
	if [ -z "$LEAKS_RESULT" ]; then
		echo -e "${CIANE}LEAKS: ${RED}KO${NC}"
		((ERRORS++))
	else
		echo -e "${CIANE}LEAKS: ${GREEN}OK${NC}"
	fi;
	if [ -z "$ERROR_OUTPUT" ]; then
		echo -e "${CIANE}OUTPUT ERROR: ${RED}KO${NC}"
		ERRORS++
	else
		echo -e "${CIANE}OUTPUT ERROR: ${GREEN}OK${NC}"
	fi;
	echo ""
}

run_game_tests()
{
	FILE=$1
	TEST_RES_DIR=$2

	echo -e "$3 - ${LIGHT_BLUE}Testing map: ${YELLOW}${FILE}${NC}"
	echo -e "${CIANE}Playing the game..${NC}"
	valgrind --leak-check=full -s --show-leak-kinds=all ./so_long ${FILE} > ${TEST_RES_DIR} 2>&1
	LEAKS_RESULT=$(cat ${TEST_RES_DIR} | grep "All heap blocks were freed -- no leaks are possible")
	if [ -z "$LEAKS_RESULT" ]; then
		echo -e "${CIANE}LEAKS: ${RED}KO${NC}"
		((ERRORS++))
	else
		echo -e "${CIANE}LEAKS: ${GREEN}OK${NC}"
	fi;
}

# Norminette test
NORMINETTE=$(norminette *.c *.h | grep "Error!")
if [ -z "$NORMINETTE" ]; then
	RESULT="${GREEN}OK!${NC}"
else
	RESULT="${RED}KO!${NC}"
fi

echo -e "${LIGHT_BLUE}Checking norminette:${NC} ${RESULT}"
echo ""

echo -e "${RED}Testing map errors${NC}"
echo "" 
#run_test_errors maps_test/dup_exit.ber tests/dup_exit 1 ${MAP_CHR_ERR}
#run_test_errors maps_test/dup_player.ber tests/dup_player 2 ${MAP_CHR_ERR} 
#run_test_errors maps_test/invalid_path.ber tests/invalid_path 3 ${FILE_NOT_EXIST}
#run_test_errors maps_test/no_colls.ber tests/no_colls1 4 ${MAP_CHR_ERR}
#run_test_errors maps_test/no_colls2.ber tests/no_colls2 5 ${MAP_COLLECT_ERR}
#run_test_errors maps_test/no_colls3.ber tests/no_colls3 6 ${MAP_COLLECT_ERR}
#run_test_errors maps_test/no_colls4.ber tests/no_colls4 7 ${MAP_COLLECT_ERR}
#run_test_errors maps_test/no_exit.ber tests/no_exit 8 ${MAP_EXIT_ERR}
#run_test_errors maps_test/no_player.ber tests/no_player 9 ${MAP_CHR_ERR}
#run_test_errors maps_test/invalid_ext.txt tests/invalid_ext 10 ${FILE_EXT_ERR}
#run_test_errors maps_test/invalid_char.ber tests/invalid_char 11 ${MAP_CHR_ERR}
#run_test_errors maps_test/no_walls.ber tests/no_walls 12 ${MAP_WALL_ERR}
#run_test_errors maps_test/invalid_size.ber tests/invalid_size 13 ${MAP_SIZE_ERR}
#run_test_errors maps_test/rectangule1.ber tests/rectangule1 14 ${MAP_RECT_ERR}
#run_test_errors maps_test/rectangule2.ber tests/rectangule2 15 ${MAP_RECT_ERR}
#run_test_errors maps_test/rectangule3.ber tests/rectangule3 16 ${MAP_RECT_ERR}
#run_test_errors maps_test/rectangule4.ber tests/rectangule4 17 ${MAP_RECT_ERR}


echo -e "${RED}Testing game leaks${NC}"
echo "" 
run_game_tests maps_test/small_map.ber tests/small_map 1
run_game_tests maps_test/map1.ber tests/map1 2
run_game_tests maps_test/map2.ber tests/map2 3
run_game_tests maps_test/giant_map.ber tests/giant_map 4 


