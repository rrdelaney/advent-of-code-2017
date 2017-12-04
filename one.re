let string_tl = (str) => String.sub(str, 1, String.length(str) - 1);

let rec split_string = (str) =>
  switch str {
  | "" => []
  | _ => [String.make(1, str.[0]), ...split_string(string_tl(str))]
  };

let peek_list = (l) =>
  List.append(List.tl(l), [List.hd(l)]) |> List.combine(l);

let captacha = (input) =>
  split_string(input)
  |> List.map(int_of_string)
  |> peek_list
  |> List.filter(((curr, next)) => curr == next)
  |> List.map(((curr, _next)) => curr)
  |> List.fold_left((+), 0);

let circle_list = (l) =>
  List.mapi(
    (index, item) => {
      let circle_step = List.length(l) / 2;
      let circle_index = (circle_step + index) mod List.length(l);
      List.nth(l, circle_index)
    },
    l
  )
  |> List.combine(l);

let captacha2 = (input) =>
  split_string(input)
  |> List.map(int_of_string)
  |> circle_list
  |> List.filter(((curr, next)) => curr == next)
  |> List.map(((curr, _next)) => curr)
  |> List.fold_left((+), 0);
