cmake_minimum_required(VERSION 3.5)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES helpers/DataStructures.h helpers/DataStructures.cpp helpers/Printer.h helpers/Printer.cpp helpers/coutFriends.h helpers/coutFriends.cpp)

add_executable(basicTypes ${SOURCE_FILES} DMCpp/basicTypes.cpp)

add_executable(age ${SOURCE_FILES} DMCpp/1_10_1_age.cpp )

add_executable(arraysAndPointers ${SOURCE_FILES} DMCpp/1_10_2_ArraysAndPointers.cpp)

add_executable(NonOOquickSort sorting/NonOOquickSort.cpp)

add_executable(TwoSum leetcode/TwoSum.cpp ${SOURCE_FILES})

add_executable(ThreeSum leetcode/ThreeSum.cpp ${SOURCE_FILES})

add_executable(IsCompleteCycle GTraining/IsCompleteCycle.cpp ${SOURCE_FILES})

add_executable(Dust2Dust ${SOURCE_FILES} DMCpp/p93_EnvironmentDeleter.cpp)

add_executable(inorderBT ${SOURCE_FILES} leetcode/inorderBinaryTree.cpp)

add_executable(postorderBT ${SOURCE_FILES} leetcode/postOrderBT.cpp)

add_executable(polynomial DMCpp/Polynomial_2_8.h DMCpp/Polynomial_2_8.cpp)

add_executable(ruleOf6 misc/RuleOfSix.cpp)

add_executable(wiggle leetcode/WiggleSubsequence.cpp)

add_executable(countBits leetcode/CountingBitsOrOnes.cpp)

add_executable(reverseLL leetcode/LinkedListReverse.cpp)

add_executable(setZeroMatrix leetcode/SetZeroMatrix.cpp)

add_executable(burstBalloons ${SOURCE_FILES} leetcode/BurstBalloons.cpp)

#giving up:
#file(GLOB SDL_SRC "/Users/zeph/SDL/include/*.h" "/Users/zeph/SDL/src/*.h" "/Users/zeph/SDL/src/*.cpp")
add_executable(map_test ${SDL_SRC} DMCpp/GottschlingRepo/c++11/map_test.cpp)

add_executable(map_vs_unordered ${SOURCE_FILES} GTraining/Map_v_UnorderedMap.cpp)

add_executable(comboSum helpers/coutFriends.cpp helpers/coutFriends.h leetcode/ComboSumIV.cpp)

add_executable(MSS leetcode/MaxSubArray.cpp)

add_executable(missingNumber leetcode/MissingNumber.cpp)

add_executable(removeElemlent ${SOURCE_FILES} leetcode/RemoveElement.cpp)

add_executable(mergeLL leetcode/MergeLL.cpp)

add_executable(mergeSortedLists ${SOURCE_FILES} leetcode/MergeLists.cpp)

add_executable(LFU helpers/DataStructures.h helpers/DataStructures.cpp leetcode/LFU.cpp)

add_executable(heap helpers/DataStructures.h helpers/DataStructures.cpp misc/DummyMain.cpp)

add_executable(LFU2 leetcode/LFU_submitted.cpp)

add_executable(singleNum leetcode/SIngleNumber.cpp)

add_executable(dummy misc/DummyMain.cpp)

add_executable(streamingMedian leetcode/StreamingMedian.cpp)

add_executable(LongestPath leetcode/LongestFilePath.cpp)

add_executable(regexp leetcode/SimpleRegularExpressions.cpp)

add_executable(minMutations_aka_BFS leetcode/MinGeneticMutation_aka_BFS.cpp)

add_executable(addNums leetcode/AddNumbersLL.cpp)

add_executable(sortedArrayIterator GTraining/SortedArrayIterator.cpp GTraining/Main.cpp)