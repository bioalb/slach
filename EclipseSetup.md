# Preliminary #

  * Install eclipse
  * Install svn

# Steps #

From a terminal

  * svn checkout https://slach.googlecode.com/svn/trunk/ slach --username MY\_GMAIL\_ADDRESS

From eclipse (C/C++ perspective):

  * New-->project and select the location of the slach files.
  * Click on External Tools Configurations. Program-->New. Fill in location (/usr/bin/cmake), working directory (select slach directory), Arguments (.). Under the "Common" tab, select Display in Favourites menu (External Tools)
