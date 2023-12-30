from cs50 import get_string

num = get_string("Number: ")
first_numbers = []
second_digits = []
for digit_num in range(len(num)):
    if len(num) % 2 == 0:
        if digit_num % 2 == 0:
            res = int(num[digit_num]) * 2
            first_numbers.append(str(res))
        else:
            second_digits.append(int(num[digit_num]))
    else:
        if digit_num % 2 != 0:
            res = int(num[digit_num]) * 2
            first_numbers.append(str(res))
        else:
            second_digits.append(int(num[digit_num]))

first_sum = 0
for number in first_numbers:
    for digit in number:
        first_sum += int(digit)

valid = str(first_sum + sum(second_digits))[-1]

if (
    valid == "0"
    and len(num) == 15
    and (num[0] == "3" and (num[1] == "4" or num[1] == "7"))
):
    print("AMEX\n")
elif valid == "0" and len(num) == 16 and (50 < int(num[0:2]) < 56):
    print("MASTERCARD\n")
elif valid == "0" and (len(num) == 13 or len(num) == 16) and num[0] == "4":
    print("VISA\n")
else:
    print("INVALID\n")
