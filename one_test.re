let actual = One.captacha("1122");

let expected = 3;

assert (expected == actual);

let actual = One.captacha("1111");

let expected = 4;

assert (expected == actual);

let actual = One.captacha("1234");

let expected = 0;

assert (expected == actual);

let actual = One.captacha("91212129");

let expected = 9;

assert (expected == actual);

let actual = One.captacha2("1212");

let expected = 6;

assert (expected == actual);

let actual = One.captacha2("1221");

let expected = 0;

assert (expected == actual);

let actual = One.captacha2("123425");

let expected = 4;

assert (expected == actual);

let actual = One.captacha2("123123");

let expected = 12;

assert (expected == actual);

let actual = One.captacha2("12131415");

let expected = 4;

assert (expected == actual);
