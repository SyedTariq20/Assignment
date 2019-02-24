default: oss user

oss:
	gcc oss.c -o oss

user:
	gcc user.c -o user

clean:
	rm oss user
