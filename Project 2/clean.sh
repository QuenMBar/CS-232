#!/bin/bash

# clean.sh is a shell script that looks though a specified directory and its subdirectories to
# remove any "extraneous" files that are in the directories.  As it goes through it will print each file
# it removes depending on if the user added a quiet switch to the command.  If the user added the interactive
# switch, it will ask the user if they want to remove the file and if the user replies with a "y" then it will remove it.
# 
# Recieves: Can take a direcotory path, quiet swithc, and interactive switch
# 
# Written by: Quentin Barnes for CS 232
# Date: March 9, 2019



# cleanDirectory() is a fucntion that, given directory path and if it should be quiet or interactive, removes 
# "extraneous" files from the directory and its subdirectories.  
# 
# Revices: string: Directroy path, boolean: Interactive switch, boolean: Quiet switch
# 
cleanDirectory()
{	
	cd $1 																					# Moves to the specified directory
  	for file in *;do 																		# For loop trhough ever file in directory
		if [ $file = "core" ]																# Checks if the file is a "core" file
		then
			if [ "$3" = true ]																# If it shouldnt be quiet, print the file name
			then
				echo $file
			fi

			if [ "$2" = true ]																# If it shouldnt be interacive, remove the file 
			then																			# or prompt user for input and if "y" remove file
				rm $file
			else
				echo "Do you want to remove " $file "? Reply \"y\" for yes."
				read respone
				if [ -n "$respone" ]
				then
					if [ $respone = "y" ]
					then 
						rm $file
					fi
				fi
			fi
		fi
		if [[ (${file: -1} = "#") && (${file:0:1} = "#") ]]									# Checks if the file starts and ends with #
		then
			if [ "$3" = true ]																# If it shouldnt be quiet, print the file name
			then
				echo $file
			fi

			if [ "$2" = true ]																# If it shouldnt be interacive, remove the file 
			then																			# or prompt user for input and if "y" remove file
				rm $file
			else
				echo "Do you want to remove " $file "? Reply \"y\" for yes."
				read respone
				if [ -n "$respone" ]
				then
					if [ $respone = "y" ]
					then 
						rm $file
					fi
				fi
			fi
		fi
		if [ ${file: -1} = "~" ]															# Checks if the file ends with ~
		then
			if [ "$3" = true ]																# If it shouldnt be quiet, print the file name
			then
				echo $file
			fi

			if [ "$2" = true ]																# If it shouldnt be interacive, remove the file 
			then																			# or prompt user for input and if "y" remove file
				rm $file
			else
				echo "Do you want to remove " $file "? Reply \"y\" for yes."
				read respone
				if [ -n "$respone" ]
				then
					if [ $respone = "y" ]
					then 
						rm $file
					fi
				fi
			fi
		fi
		if [ ${file: -2} = ".o" ]															# Checks if the file ends with ".o"
		then
			if [ "$3" = true ]																# If it shouldnt be quiet, print the file name
			then
				echo $file
			fi

			if [ "$2" = true ]																# If it shouldnt be interacive, remove the file 
			then																			# or prompt user for input and if "y" remove file
				rm $file
			else
				echo "Do you want to remove " $file "? Reply \"y\" for yes."
				read respone
				if [ -n "$respone" ]
				then
					if [ $respone = "y" ]
					then 
						rm $file
					fi
				fi
			fi
		fi
		if [[ (-x $file) && (! -d $file) ]]													# Checks if the file is an executable
		then
			if [ "$3" = true ]																# If it shouldnt be quiet, print the file name
			then
				echo $file
			fi

			if [ "$2" = true ]																# If it shouldnt be interacive, remove the file 
			then																			# or prompt user for input and if "y" remove file
				rm $file
			else
				echo "Do you want to remove " $file "? Reply \"y\" for yes."
				read char
				if [ -n "$char" ]
				then
					if [ $char = "y" ]
					then 
						rm $file
					fi
				fi
			fi
		fi
		if [ -d $file ]																		# Checks if the file is an executable
		then 
			if [ "$3" = true ]																# If it shouldnt be quiet, print that its changing directory
			then
				echo "MOVING TO DIRECTORY: " $file
			fi
			cleanDirectory $file $2 $3														# Calls the cleanDirectory for the sub-directory
			cd ..																			# Returns to previous direcotry after sub-directory is clean
		fi
	done
}



# Main
# Takes the command line arguments and uses them to call cleanDirectory() with the propper arguments
# 
# Can take a direcotory path, quiet swithc, and interactive switch
# 
if [ $# -gt 0 ]																				# If there is command line arguments then parse them
then
	autoDel=true
	notQuiet=true
	default="."
	for i in $@; do 																		# For every command line argument entered
		echo "Arguments supplied: $i" 
		if [[ ($i = "-i") || ($i = "--interactive") ]]										# If its the interactive switch, 
		then 
			autoDel=false 																	# then set the interact variable to false
		elif [[ ($i = "-q") || ($i = "--quiet") ]]											# If its the quiet switch, 
		then 
			notQuiet=false																	# then set the quiet variable to false
		else
			default=$i 																		# else set the path to the switch
		fi
	done
	cleanDirectory $default $autoDel $notQuiet												# call cleanDirectory() with inputed values
else																						# else call cleanDirectory() with default values
	echo "No arguments supplied"
	cleanDirectory . true true
fi

echo "DONE"																					# Tells the user that the program is finished