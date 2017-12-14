module StringSet = Set.Make(String);

module StringMap = Map.Make(String);

let create_bank = (input) =>
  String.split_on_char(' ', input) |> List.map(int_of_string) |> Array.of_list;

let hash_bank = Array.fold_left((s, num) => s ++ "|" ++ string_of_int(num), "");

let show_bank = (bank) => hash_bank(bank) |> print_endline;

let distribute = (bank) => {
  let bank_len = Array.length(bank);
  let (max_block_index, max_block_value) =
    Array.mapi((value, index) => (value, index), bank)
    |> Array.fold_left(
         ((high_index, high_value), (index, value)) =>
           if (value > high_value) {
             (index, value)
           } else {
             (high_index, high_value)
           },
         (0, min_int)
       );
  let blocks = ref(max_block_value);
  bank[max_block_index] = 0;
  while (blocks^ > 0) {
    let index = (max_block_index + 1 + max_block_value - blocks^) mod bank_len;
    bank[index] = bank[index] + 1;
    blocks := blocks^ - 1
  }
};

let steps_to_loop = (input) => {
  let steps = ref(0);
  let previous = ref(StringSet.empty);
  let bank = create_bank(input);
  while (! StringSet.mem(hash_bank(bank), previous^)) {
    previous := StringSet.add(hash_bank(bank), previous^);
    steps := steps^ + 1;
    distribute(bank)
  };
  steps^
};

let steps_to_loop2 = (input) => {
  let steps = ref(0);
  let previous = ref(StringMap.empty);
  let bank = create_bank(input);
  while (! StringMap.mem(hash_bank(bank), previous^)) {
    previous := StringMap.add(hash_bank(bank), steps^, previous^);
    steps := steps^ + 1;
    distribute(bank)
  };
  let last_seen = StringMap.find(hash_bank(bank), previous^);
  steps^ - last_seen
};