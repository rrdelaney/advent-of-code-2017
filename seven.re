module StringSet = Set.Make(String);

module Program = {
  type t = {
    name: string,
    weight: int,
    mutable children: list(t)
  };
  let make = (name, weight) => {name, weight, children: []};
  let rec child_weight = (program) =>
    switch program.children {
    | [] => program.weight
    | children => program.weight + (List.map(child_weight, children) |> List.fold_left((+), 0))
    };
};

module StrUtil = {
  let remove_comma = (str) =>
    if (str.[String.length(str) - 1] == ',') {
      String.sub(str, 0, String.length(str) - 1)
    } else {
      str
    };
  let strip_parens = (str) => String.sub(str, 1, String.length(str) - 2);
};

let program_of_line = (line) => {
  let (name, weight, children) =
    switch (String.split_on_char(' ', line)) {
    | [name, weight] =>
      let weight = weight |> StrUtil.strip_parens |> int_of_string;
      (name, weight, [])
    | [name, weight, _arrow, ...children] =>
      let weight = weight |> StrUtil.strip_parens |> int_of_string;
      let children = children |> List.map(StrUtil.remove_comma);
      (name, weight, children)
    | _ => raise(Not_found)
    };
  let program = Program.make(name, weight);
  (program, children)
};

let parse_input = (input) => String.split_on_char('\n', input) |> List.map(program_of_line);

let build_tree = (programs) => {
  open Program;
  let get_by_name = (pname) =>
    List.find((({name}, _)) => pname == name, programs) |> (((p, _)) => p);
  let root_name = {
    let all_names = List.map((({name}, _)) => name, programs) |> StringSet.of_list;
    let all_children =
      List.map(((_, c)) => c, programs)
      |> List.map(StringSet.of_list)
      |> List.fold_left(StringSet.union, StringSet.empty);
    StringSet.diff(all_names, all_children) |> StringSet.choose
  };
  List.iter(((program, children)) => program.children = List.map(get_by_name, children), programs);
  let tree_nodes = List.map(((p, _)) => p, programs);
  List.find(({name}) => name == root_name, tree_nodes)
};

let find_root_name = (input) => parse_input(input) |> build_tree |> (({name}: Program.t) => name);