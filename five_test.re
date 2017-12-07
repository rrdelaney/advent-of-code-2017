let actual = Five.num_steps("0\n3\n0\n1\n-3");

let expected = 5;

assert (expected == actual);

let actual = Five.num_steps2("0\n3\n0\n1\n-3");

let expected = 10;

assert (expected == actual);