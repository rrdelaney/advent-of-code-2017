let jump = (~increment, offsets) => {
  let steps = ref(0);
  let ptr = ref(0);
  while (ptr^ < Array.length(offsets)) {
    steps := steps^ + 1;
    let next_ptr = ptr^ + offsets[ptr^];
    offsets[ptr^] = increment(offsets[ptr^]);
    ptr := next_ptr
  };
  steps^
};

let add_one = (value) => value + 1;

let num_steps = (instructions) =>
  String.split_on_char('\n', instructions)
  |> List.map(int_of_string)
  |> Array.of_list
  |> jump(~increment=add_one);

let increment2 = (value) =>
  if (value >= 3) {
    value - 1
  } else {
    value + 1
  };

let num_steps2 = (instructions) =>
  String.split_on_char('\n', instructions)
  |> List.map(int_of_string)
  |> Array.of_list
  |> jump(~increment=increment2);