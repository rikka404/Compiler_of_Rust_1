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

// fn sum(mut a: i32, mut b: i32) -> i32 {
//     return a + b;
// }

// fn main() {
//     let mut a:i32 = 5;
//     {
//         let mut b:i32;
//         a = -sum(4 / 2, 2 + a * 2);
//     }
//     let mut b:i32 = 4;
// }

// fn main() {
//     let mut c:i32 = 5;
//     let mut a:& & i32 = & & *&c;
//     let mut b:&i32 = *a;
// }

// fn main() {
//     let mut c:i32 = 5;
//     let mut d:i32 = 6;
//     let mut a:&mut i32;
//     a = &mut c;
//     a = &mut d;
//     *a = 10;
// }

// fn main() {
//     let mut c:i32 = 5;
//     let mut a:&mut &mut i32 = &mut &mut *&mut c;
//     **a = 9 + **a;
// }


fn sum(mut a: &mut &mut i32, mut b: i32) -> i32 {
    **a += 1;
    return **a + b;
}

// fn sum2(mut a:i32, mut b:i32)->i32{
//     if a > 1{
//         if 1 {
//             let mut c = 2;
//         }
//         else {
//             let mut c = 1;
//         }
//         1
//     }
//     else{
//         2
//     }
// }

fn main() {
    let mut a:i32 = 5;
    let mut b:i32 = 10;
    while a > 1
    {
        a = a - 1;
    }
    // sum(&mut &mut a, b);
    // let mut d = sum2(a, b);
    // let mut c = {
    //     let mut d:i32 = 2;
    //     let mut e = 1;
    //     d + e
    // };
}

// fn main() {
//     loop
//     {
//         a = a - 1;
//         break;
//         break;
//         continue;
//         continue;
//     }
// }