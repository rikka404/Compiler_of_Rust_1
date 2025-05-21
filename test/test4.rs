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


// fn sum(mut a: &mut &mut i32, mut b: i32) -> i32 {
//     **a += 1;
//     return **a + b;
// }

// fn sum2(mut a:i32, mut b:i32)->i32{
//     if a > 1{
//         if 1 {
//             let mut c = 2;
//         }
//         else {
//             let mut c = 1;
//             let mut d = 2;
//         }
//         1
//     }
//     else{
//         2
//     }
// }

fn main1() {
    let mut a:i32 = 5;
    let mut b:i32 = 10;
    let mut c:i32 = loop{
        let mut c = 1;
        if c > 1
        {
            break 1;
        }
        else
        {
            break 0;
        }
    };
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

// fn main() {
//     let mut a:i32 = 5;
//     let b:&i32 = &a;
//     // while a == *b {
//     //     a += 1;
//     //     break;
//     // }
//     for i in 0..*b {
//         if (a > 10 || a < 0) {
//             break;
//         }
//         a += 1;
//     }
// }

// fn main() {
//     // let mut c = 1;
//     // let mut a:[i32;4];
//     // {
//     //     a = [1, 2, c + 1, 4];
//     // }
//     let mut b:[[i32;2];2];
//     {
//         b = [[1, 2], [4, 5]];
//     }
//     b[1][1] += b[1][0];
// }

// fn main() {
//     let mut a:(i32, [i32; 2]) = (3, [1, 2]);
//     let mut b= (6, (4, 5));
//     a.1[1] += b.1.0;
// }

// fn sum(mut b:&mut (i32, [i32; 2])) {
//     (*b).1[0] = (*b).0 + 1;
// }

// fn main() {
//     let mut a:(i32, [i32; 2]);
//     {
//         a = (3, [1, 2]);
//     }
//     sum(&mut a);
// }

// fn main() {
//     let mut a:[i32;4] = [0,1,2,3];
//     // for i in *&a {
//     //     if (i == 1)
//     //     {
//     //         continue;
//     //     }
//     // }
//     for mut i in 0..4 {
//         a[i] += 1;
//     }
// }

// fn main(){
//     let mut a:i32 = 5;
//     if true {
//         a = 6;
//     }
//     if false {
//         a = 7;
//     }
// }

fn main() {
    let mut a = 5/2+3*2;
    let b = &a;
    let mut c = 3 + *b * 2;
}