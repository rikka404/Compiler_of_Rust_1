// fn main(mut c:i32, mut d:i32) -> i32 {
//     let mut a = 10;
//     let mut a;
//     a = 5;
//     {
//         let mut b:i32;
//         b = (3);
//         {
//             let mut c = a;
//             c += 2;
//             return 3;
//         }
//     }
//     let mut b:i32;
//     b = 1;
//     c += 1;
//     b = (c + 1) * a - b;
//     return c;
// }

fn sum(mut a: i32, mut b: i32) -> i32 {
    return a + b;
}

fn main() {
    let mut a:i32 = 5;
    {
        let mut b:i32;
        a = sum(4 / 2, 2 + a * 2);
    }
    let mut b:i32 = 4;
    loop
    {
        a = a - 1;
    }
}