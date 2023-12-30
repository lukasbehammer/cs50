from cs50 import get_string
import re

text = get_string("Text: ")

words_result = re.findall(" ", text)
words_n = len(words_result) + 1

sentences_result = re.findall("[!.?]", text)
sentences_n = len(sentences_result)

letters_result = re.findall("[A-Za-z]", text)
letters_n = len(letters_result)

letters_per_hundred_words = (letters_n / words_n) * 100
sentences_per_hundred_words = (sentences_n / words_n) * 100

index = round(
    0.0588 * letters_per_hundred_words - 0.296 * sentences_per_hundred_words - 15.8
)
if index < 1:
    print(f" Before Grade 1")
elif index >= 16:
    print(f"Grade 16+")
else:
    print(f"Grade {index}")
