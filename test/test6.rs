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
    let mut a: i32;
    input a;
    let b = &mut a;
    if (a + 5 > 10)
    {
        output sum(a, a);
    }
    else
    {
        *b = 10;
        output a;
    }
}