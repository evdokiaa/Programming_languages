(* Input parse code by Stavros Aronis, modified by Nick Korasidis. *)
fun parse file =
    let
	(* A function to read an integer from specified input. *)
        fun readInt input = 
	    Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)

	(* Open input file. *)
    	val inStream = TextIO.openIn file

        (* Read an integer (number of countries) and consume newline. *)
	val n = readInt inStream
        val k = readInt inStream

	val _ = TextIO.inputLine inStream

        (* A function to read N integers from the open file. *)
	fun readInts 0 acc = acc (* Replace with 'rev acc' for proper order. *)
	  | readInts i acc = readInts (i - 1) (readInt inStream :: acc)
    in
   	(n, k, readInts n [])
    end



fun E1(n,k,c_found,i,j,min_chain,found,color) = if ((n=i) andalso(c_found<k))
                                                then(
  if (min_chain=n+1) then print ("0\n")
  else (print(Int.toString(min_chain)^ "\n")))
  else(
        if (c_found<k) then (
                if ( Array.sub(found,(Array.sub(color,i))) = 0) then (        
                let 
                val
                  update=Array.update(found,Array.sub(color,i),Array.sub(found,Array.sub(color,i))+1)
                in 
                E1(n,k,c_found+1,i+1,j,min_chain,found,color)
                end)
                else(
                let 
                val
                 update=Array.update(found,Array.sub(color,i),Array.sub(found,Array.sub(color,i))+1)
                in 
                E1(n,k,c_found,i+1,j,min_chain,found,color)
                end)
                ) 
        else(
                if(c_found=k) then (
                let
                  val a=E2(j+1,found,color,i)
                in
                if (min_chain>i-a) then E1(n,k,c_found-1,i,a,i-a,found,color)
                else (E1(n,k,c_found-1,i,a,min_chain,found,color))
                end)
                else (print(Int.toString(min_chain)))
         
         )
         )
        

and E2(j,found,color,i)=
  let
    val
    update=Array.update(found,Array.sub(color,j),Array.sub(found,Array.sub(color,j))-1)
  in
    if (Array.sub(found,Array.sub(color,j))=0) then j
    else E2(j+1,found,color,i)
 end
 
fun dilosi(n,k,xromata)=
     let
       val chandler = Array.fromList(xromata)
       val f = Array.array(k+1,0)
     in 
       E1(n,k,0,0,~1,n+1,f,chandler)
  end


fun colors fileName = dilosi (parse fileName)



