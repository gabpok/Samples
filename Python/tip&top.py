#! python3

# Tip and toe game for 2 players. The program asks about users' names and writes results to file.
# Code of program is based on task from https://www.practicepython.org/exercise/2016/08/03/29-tic-tac-toe-game.html

import sys
import datetime

#Drawing board
def game_board(x):
    print(" --- " * 3)
    print("| %s  | %s |  %s | " % (str(x[0][0]), str(x[0][1]), str(x[0][2])))
    print(" --- " * 3)
    print("| %s  | %s |  %s | " % (str(x[1][0]), str(x[1][1]), str(x[1][2])))
    print(" --- " * 3)
    print("| %s  | %s |  %s | " % (str(x[2][0]), str(x[2][1]), str(x[2][2])))
    print(" --- " * 3)

#Checking if the board is full
def check_game(a):
    if a[0][0] != "." and a[0][1] != "." and a[0][2] != "." and a[1][0] != "." and a[1][1] != "." and a[1][2] != "." and a[2][0] != "." and a[2][1] != "." and a[2][2] != ".":
        return 1
    else:
        return 0

#Writing results to file
def write_to_file(x):
    name = "game_results.txt"
    date = datetime.date.today()
    with open(name, 'w') as file:
        file.write("%s: %s wins" % (date, x))

#Checking who gets the highest value of points
def check_point(x,y,q,w):
    if x > y:
        if x <= 1:
            print("%s wins with %s point" % (q, str(x)))
        else:
            print("%s wins with %s points" % (q, str(x)))
        write_to_file(q)
    elif x < y:
        if y <= 1:
            print("%s wins with %s point" % (w, str(x)))
        else:
            print("%s wins with %s points" % (w, str(x)))
        write_to_file(w)
    elif x == y:
        print("Both players have the same value of points")

#Function to ask if players still want to play
def play_again(a,x,y,q,w):
    while a:
        answer = input("Do you want play again? ")
        if answer == "yes":
            continue
        elif answer == "no":
            check_point(x,y,q,w)
            sys.exit()

#Getting players choice and putting to arrays
def play1_answer(a,x,y,q,w):
    while a:
        if check_game(a) == 0:
            x,y = input("%s, which row, column " % q).split(',')
            if a[int(x)-1][int(y)-1] != ".":
                print("This place is occupied, try again")
                continue
            else :
                a[int(x) - 1][int(y) - 1] = "X"
                return a
        elif check_game(a) == 1:
            print("Game over!")
            play_again(a,x,y,q,w)

def play2_answer(a,x,y,q,w):
    while a:
        if check_game(a) == 0:
            x1, y1 = input("%s, which row, column " % w).split(',')
            if a[int(x1)-1][int(y1)-1] != ".":
                print("This place is occupied, try again")
                continue
            else:
                a[int(x1) - 1][int(y1) - 1] = "O"
                return a
        elif check_game(a) == 1:
            print("Game over!")
            play_again(a,x,y,q,w)

#Checking rows, columns and diagonals
def check_winner(a,z,y,q,w):
    #check columns
    for x in range(0,3):
        if a[0][x] == a[1][x] == a[2][x]:
            if a[0][x] == "X":
                print("%s wins!" % q)
                z +=1
                play_again(a,z,y,q,w)
            elif a[0][x] == "O":
                print("%s wins!" % w)
                y += 1
                play_again(a,z,y,q,w)
    #check rows
    for x in range(0, 3):
        if a[x][0] == a[x][1] == a[x][2]:
            if a[x][0] == "X":
                print("%s wins!" % q)
                z += 1
                play_again(a,z,y,q,w)
            elif a[x][0] == "O":
                print("%s wins!" % w)
                y += 1
                play_again(a,z,y,q,w)
    #check diagonals
    if a[0][0] == a[1][1] == a[2][2] or a[0][2] == a[1][1] == a[2][0]:
        if a[1][1] == "X":
            print("%s wins!" % q)
            z += 1
            play_again(a,z,y,q,w)
        elif a[1][1] == "O":
            print("%s wins!" % w)
            y += 1
            play_again(a,z,y,q,w)

if __name__ == "__main__":
    play1_val = 0
    play2_val = 0
    board = [[".",".","."] for x in range(3)]
    user1 = input("Name of player 1: ")
    user2 = input("Name of player 2: ")

    while not False:
            play1_answer(board, play1_val, play2_val, user1, user2)
            check_winner(board, play1_val, play2_val, user1, user2)
            game_board(board)
            play2_answer(board, play1_val, play2_val, user1, user2)
            check_winner(board, play1_val, play2_val, user1, user2)
            game_board(board)

