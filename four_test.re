let actual =
  Four.valid_passwords("aa bb cc dd ee\naa bb cc dd aa\naa bb cc dd aaa");

let expected = 2;

assert (expected == actual);

let actual =
  Four.valid_passwords2(
    "abcde fghij\nabcde xyz ecdab\na ab abc abd abf abj\niiii oiii ooii oooi oooo\noiii ioii iioi iiio"
  );

let expected = 3;

assert (expected == actual);
