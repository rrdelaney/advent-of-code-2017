module StringSet = Set.Make(String);

exception Too_many;

let validate = (password) =>
  String.split_on_char(' ', password)
  |> List.fold_left(
       (words, word) =>
         if (StringSet.mem(word, words)) {
           raise(Too_many)
         } else {
           StringSet.add(word, words)
         },
       StringSet.empty
     );

let is_valid_password = (~validator, password) =>
  try (validator(password) |> ((_) => true)) {
  | Too_many => false
  };

let valid_passwords = (passwords) =>
  String.split_on_char('\n', passwords)
  |> List.filter(is_valid_password(~validator=validate))
  |> List.length;

let sort_string = (str) => {
  let string_tl = (str) => String.sub(str, 1, String.length(str) - 1);
  let rec split_string = (str) =>
    switch str {
    | "" => []
    | _ => [String.make(1, str.[0]), ...split_string(string_tl(str))]
    };
  split_string(str) |> List.sort(compare) |> String.concat("")
};

let no_anagrams = (password) =>
  String.split_on_char(' ', password)
  |> List.fold_left(
       (words, word) => {
         let word = sort_string(word);
         if (StringSet.mem(word, words)) {
           raise(Too_many)
         } else {
           StringSet.add(word, words)
         }
       },
       StringSet.empty
     );

let valid_passwords2 = (passwords) =>
  String.split_on_char('\n', passwords)
  |> List.filter(is_valid_password(~validator=no_anagrams))
  |> List.length;
