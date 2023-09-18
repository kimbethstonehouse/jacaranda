define i32 @maths(i32 %0, i32 %1, i32 %2, i32* %3, i32 %4, i32* %5, i32 %6) {
block0start:
  %7 = alloca i32
  %8 = alloca i32*
  %9 = alloca i32*
  %10 = alloca i32
  %11 = alloca i32
  %12 = alloca i32
  %13 = alloca i32*
  %14 = alloca i32
  %15 = alloca i32*
  %16 = alloca i32
  br label %block1start
block1start:                                      ; preds = %block0start
  br label %block2start
block2start:                                      ; preds = %block1start
  %17 = load i32, i32* %10
  %18 = alloca i32
  store i32 %17, i32* %18
  %19 = load i32, i32* %18
  %20 = icmp eq i32 %19, 0
  %21 = alloca i1
  store i1 %20, i1* %21
  %22 = load i1, i1* %21
  br i1 %22, label %block1end, label %block2startelse
block2startelse:                                  ; preds = %block2start
  %23 = load i32, i32* %11
  %24 = alloca i32
  store i32 %23, i32* %24
  %25 = load i32, i32* %12
  %26 = alloca i32
  store i32 %25, i32* %26
  %27 = load i32, i32* %26
  %28 = load i32, i32* %24
  %29 = add i32 %27, %28
  store i32 %29, i32* %24
  %30 = load i32, i32* %24
  store i32 %30, i32* %10
  br label %block3start
block3start:                                      ; preds = %block2startelse
  %31 = load i32, i32* %11
  %32 = alloca i32
  store i32 %31, i32* %32
  %33 = load i32, i32* %32
  %34 = icmp eq i32 %33, 0
  %35 = alloca i1
  store i1 %34, i1* %35
  %36 = load i1, i1* %35
  br i1 %36, label %block2end, label %block3startelse
block3startelse:                                  ; preds = %block3start
  %37 = load i32, i32* %10
  %38 = alloca i32
  store i32 %37, i32* %38
  %39 = load i32, i32* %12
  %40 = alloca i32
  store i32 %39, i32* %40
  %41 = load i32, i32* %40
  %42 = load i32, i32* %38
  %43 = add i32 %41, %42
  store i32 %43, i32* %38
  %44 = load i32, i32* %38
  ret i32 %44
block2end:                                        ; preds = %block3start
  %45 = load i32, i32* %12
  %46 = alloca i32
  store i32 %45, i32* %46
  %47 = load i32, i32* %46
  %48 = icmp eq i32 %47, 0
  %49 = alloca i1
  store i1 %48, i1* %49
  %50 = load i1, i1* %49
  br i1 %50, label %block0end, label %block2endelse
block2endelse:                                    ; preds = %block2end
  %51 = load i32, i32* %10
  %52 = alloca i32
  store i32 %51, i32* %52
  %53 = alloca i32
  store i32 0, i32* %53
  %54 = load i32, i32* %53
  %55 = load i32, i32* %52
  %56 = add i32 %54, %55
  store i32 %56, i32* %52
  %57 = load i32, i32* %52
  ret i32 %57
block1end:                                        ; preds = %block2start
  %58 = alloca i32
  store i32 0, i32* %58
  %59 = load i32, i32* %11
  %60 = alloca i32
  store i32 %59, i32* %60
  %61 = load i32, i32* %60
  %62 = load i32, i32* %58
  %63 = add i32 %61, %62
  store i32 %63, i32* %58
  %64 = load i32, i32* %58
  store i32 %64, i32* %10
  br label %block0end
block0end:                                        ; preds = %block1end, %block2end
  %65 = load i32, i32* %10
  %66 = alloca i32
  store i32 %65, i32* %66
  %67 = load i32, i32* %66
  ret i32 %67
}
