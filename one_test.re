let expected = One.captacha("1122");

let actual = 3;

assert (actual == expected);

let expected = One.captacha("1111");

let actual = 4;

assert (actual == expected);

let expected = One.captacha("1234");

let actual = 0;

assert (actual == expected);

let expected = One.captacha("91212129");

let actual = 9;

assert (actual == expected);

let actual = One.captacha2("1212");

let expected = 6;

assert (actual == expected);

let actual = One.captacha2("1221");

let expected = 0;

assert (actual == expected);

let actual = One.captacha2("123425");

let expected = 4;

assert (actual == expected);

let actual = One.captacha2("123123");

let expected = 12;

assert (actual == expected);

let actual = One.captacha2("12131415");

let expected = 4;

assert (actual == expected);
