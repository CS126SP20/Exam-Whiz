# Exam Whiz

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)
This project was made for my CS126 Final project and then later the the functionality of this project was extended

The aim for this project is to create an exam system which can help teachers administer tests. The student can login enter the test code and take the test. While the software automatically grades the tests. The teacher can login and see the performances of the class for each question and the test on an average.

The code base was tested on macOS and currently works only on macOS. The libraries used to create this project are - 
* [Cinder](https://libcinder.org)
* [Cinder-Imgui](https://github.com/simongeilfus/Cinder-ImGui)
* [sqlite_modern_cpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp) 

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

## Setting up Cinder + Exam System
* Download Cinder (v0.9.2) for your platform. Extract the downloaded item into a folder. We’ll call this folder ~/Cinder throughout the instructions
* Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. You only need to do this once per machine. This build might take a while.
* Create a directory, say my-projects in ~/Cinder. Clone the snake project into this folder. You can checkout your repository here:
* Open the exam_system project in CLion, set the target to cinder-myapp and click the run button.

### Setting up the Database (SQLite)
* In CLion, navigate to View > Tool Windows > Database.
* Next, in the Database window, select the Database properties button, which is between the Refresh and the Stop button.
* There are two possibilities now: i. If properties for database.db are automatically selected, you can proceed to Step 4. ii. If there are no database properties selected, navigate to Add > SQLite.
* Next, there should be a highlighted link to download the necessary drivers for SQLite. Click this link.
* For the file of the datasource, select final-project-aparekh5/assets/database.db.
* Press Test Connection to verify that the driver is set up correctly. Click the OK button in the
* Now, you should run the cinder-snake target and play the game to test out your database.
* After the cinder-snake application has run, go back to the Database tab, click the Refresh button. You should now be able to see the schema of the database under database.db > schemas > main


---
To Directly build and run the application go to final-project > cmake-build-debug > Debug > cinder-myapp > cinder-myapp.app

**Author**: Aryaman Parekh - [`aparekh5@illinois.edu`](mailto:aparekh5@illinois.edu)
