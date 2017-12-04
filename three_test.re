let actual = Three.manhattan_distance(1);

let expected = 0;

assert (expected == actual);

let actual = Three.manhattan_distance(12);

let expected = 3;

assert (expected == actual);

let actual = Three.manhattan_distance(23);

let expected = 2;

assert (expected == actual);

let actual = Three.manhattan_distance(1024);

let expected = 31;

assert (expected == actual);

print_int(Three.manhattan_distance(277678));
