CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/account.c \
	  src/accountExist.c \
	  src/accountInfo.c \
	  src/auth.c \
	  src/changePass.c \
	  src/createAccount.c \
	  src/dipositMoney.c \
	  src/login.c \
	  src/main.c \
	  src/transaction.c \
	  src/transferMoney.c \
	  src/usermenu.c 

TARGET = bank

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(TARGET)