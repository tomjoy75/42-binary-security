first_part = "756e505234376848"
second_part = "45414a3561733951"
third_part = "377a7143574e6758"
forth_part = "354a35686e475873"
fifth_part = "48336750664b394d"

flag = bytearray.fromhex(
	fifth_part +
	forth_part +
	third_part +
	second_part +
	first_part
).decode('ascii')

print(flag[::-1])