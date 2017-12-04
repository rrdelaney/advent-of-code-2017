let flat_map = (mapper) => List.map(List.map(mapper));

let parse_sheet = (sheet) =>
  String.split_on_char('\n', sheet)
  |> List.map(String.split_on_char(' '))
  |> flat_map(int_of_string);

let row_max = List.fold_left(max, min_int);

let row_min = List.fold_left(min, max_int);

let row_diff = (row) => row_max(row) - row_min(row);

let checksum = (sheet) =>
  parse_sheet(sheet) |> List.map(row_diff) |> List.fold_left((+), 0);

let is_divisible = (a, b) => a mod b == 0;

let reverse_compare = (a, b) => compare(b, a);

let rec row_quotient = (row) =>
  switch row {
  | [] => raise(Not_found)
  | [dividend, ...tail] =>
    let can_divide = is_divisible(dividend);
    switch (List.find(can_divide, tail)) {
    | divisor => dividend / divisor
    | exception Not_found => row_quotient(tail)
    }
  };

let checksum2 = (sheet) =>
  parse_sheet(sheet)
  |> List.map(List.sort(reverse_compare))
  |> List.map(row_quotient)
  |> List.fold_left((+), 0);
