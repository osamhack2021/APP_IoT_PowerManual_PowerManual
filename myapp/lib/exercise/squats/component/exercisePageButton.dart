



import 'package:flutter/material.dart';
import 'package:mobx/mobx.dart';
import 'package:myapp/Font.dart';
import '../page/afterSquats.dart';
class ExercisePageButoon extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return Container(
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
           ElevatedButton(
            onPressed: (){
              /*Navigator.push(
                context,
                 MaterialPageRoute(builder: (context)=> ()))
               );*/
            },
           child: Text("자세 설명 보기", style: KorHeaderStyle,)
           ),
           SizedBox(width: 30,),
           ElevatedButton(
            onPressed: (){
              Navigator.push(
                 context,
                 MaterialPageRoute(builder: (context)=> AfterSquats())
              );
            },
                 child: Text("다음세트로", style: KorHeaderStyle,)),
                 
        ],
      ),
    );
}
}