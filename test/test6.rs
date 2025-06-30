// fn main()
// {
//     let a: i32 = 4;
//     let mut b: i32 = 5;
//     {
//         let a: bool = true;
//         let a: i32 = 6;
//         {
//             let mut b: i32 = 7;
//             b = a;
//             out b; // 6
//         }
//         out b; // 5
//     }
//     b += a;
//     out b; // 9
// }

fn sum(a: i32, b: i32) -> i32
{
    return a + b;
}

fn main()
{
    let a = 7;
    out sum(a, a + a);
}