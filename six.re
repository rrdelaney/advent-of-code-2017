module Prime = {
  module IntMap = Map.Make(Int64);
  let is_prime = (number) => {
    let is = ref(true);
    for (i in number downto 1) {
      is := is^ && number mod i == 0
    };
    is^
  };
  let cache = ref(IntMap.empty |> IntMap.add(Int64.zero, 2));
  let calc = () => {
    let (_, last_prime) = IntMap.max_binding(cache^);
    let next_prime = ref(last_prime);
    while (! is_prime(next_prime^)) {
      next_prime := next_prime^ + 1
    };
    next_prime^
  };
  let get = (nth) =>
    try (IntMap.find(nth, cache^)) {
    | Not_found =>
      let prime = calc();
      cache := IntMap.add(nth, prime, cache^);
      prime
    };
};

module IntSet = Set.Make(Int32);

let create_bank = (input) =>
  String.split_on_char(' ', input) |> List.map(int_of_string) |> Array.of_list;

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
    let index = (max_block_value - blocks^) mod bank_len;
    bank[index] = bank[index] + 1;
    blocks := blocks^ - 1
  }
};

let hash_bank = (bank) =>
  Array.mapi(
    (index, value) =>
      Int64.of_int(index)
      |> Prime.get
      |> float_of_int
      |> ((n) => n ** float_of_int(value))
      |> int_of_float,
    bank
  )
  |> Array.fold_left((+), 0)
  |> Int32.of_int;

let steps_to_loop = (input) => {
  let steps = ref(1);
  let previous = ref(IntSet.empty);
  let bank = create_bank(input);
  while (! IntSet.mem(hash_bank(bank), previous^)) {
    previous := IntSet.add(hash_bank(bank), previous^);
    steps := steps^ + 1;
    distribute(bank)
  };
  steps^ + 1
};