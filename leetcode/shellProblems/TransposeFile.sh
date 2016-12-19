#!/usr/bin/env bash

# not terrible interesting: http://stackoverflow.com/questions/1729824/transpose-a-file-in-bash
/**
Skip
Transpose File
Difficulty: Medium

Given a text file file.txt, transpose its content.

You may assume that each row has the same number of columns and each field is separated by the ' ' character.

For example, if file.txt has the following content:

name age
alice 21
ryan 30
Output the following:

name alice ryan
age 21 30
**/

# Read from the file file.txt and print its transposed content to stdout.