#!/usr/bin/env zsh
#
# ???
#
# Dependencies:
#   fd
#     github.com/sharkdp/fd
#
# BeyondMagic © 2022-2023 <beyondmagic@mail.ru>

# To colorise output uniquely.
function gray  () { echo "\033[2m$1\033[0m" }
function bold  () { echo "\033[3m$1\033[0m" }
function red   () { echo "\033[31m$1\033[m" }
function green () { echo "\033[32m$1\033[m" }

function build ()
{
  bear -- make build -s
  mv compile_commands.json "$last_dir"
}

case "$1" in

  # Will build 
  #  $2? Name of the project in case of root folder.
  'run' | 'r' )

    # If it the root folder.
    if [ -f "config.mk" ]; then

      if [ ! "$2" ]; then
        red "\$2 argument should be the problem's folder name."
        exit 1
      fi
      if [ ! -f "./$2/" ]; then
        red "\"$2\" problem's folder does not exist."
        exit 1
      fi
      export c="$(echo source.* | awk -F '[.]' '{print $NF}')"
      n="$2" build
    else
      last_dir="$PWD"
      export c="$(echo source.* | awk -F '[.]' '{print $NF}')"
      cd "../"
      n="$(basename "$last_dir")" build
      cd "$last_dir"
    fi
  ;;

  # To create a new folder for a problem.
  # @parameters
  #  $2 To create a new run of files.
  #  $3 The quantity of problems.
  #  $4 C++ or C. C++ by default.
  'create' | 'c' )

    # Verify if user's on the root path.
    if [ ! -f "config.mk" ]; then
      red "You have to be on the root path of the project to create a problem's folder."
      exit 1
    fi

    # Verify if user is on the root of the project.
    if [ ! "$2" ]; then
      red "Specify the name's problem following the convention."
      exit 1
    fi

    if [ -d "$2" ]; then
      red "\"$2\" folder or problem solution already exist."
      exit 1
    fi

    mkdir -p "$2/tests/"

    if [ "$4" ]; then
      name="$2/source.$4"
    else
      name="$2/source.c++"
    fi
    touch "$name"

    #cd "$2/"

    if [ "$3" -gt 0 ]; then
      for i in {1..$3}; do
        touch "./$2/tests/$i.in" "./$2/tests/$i.out"
      done

      nvim "$name" "./$2/tests"/*
    else
      nvim "$name"
    fi


  ;;

  # Will show input and output of all tests.
  # @parameters
  #  $2 how many tests.
  'test' | 't' )

    # Discover the quantity of tests.
    [ "$2" ] && quantity="$2" \
             || quantity="$(fd --base-directory tests/ --extension in --size +1b | wc -l)"

    # Run over each one.
    for a in {1..$quantity}
    do

      input="$(cat "./tests/$a.in")"
      result="$("./binary" < "./tests/$a.in")"
      expected="$(cat "./tests/$a.out")"

      if [ $? -eq 0 ]; then
        min_result="$(echo "$result" | tr -d '\r\n' | awk '{$1=$1};1')"
        min_expected="$(echo "$expected" | tr -d '\r\n' | awk '{$1=$1};1')"
        if [ "$min_result" = "$min_expected" ]; then
          green "$a. $result"
          continue
        fi
      fi
      bold "$a.  INPUT:"
      gray "$input"

      bold "$a.   RESULT:"
      red "$result"
      bold "    EXPECTED:"
      gray "$expected"

      echo
    done

  ;;

esac
