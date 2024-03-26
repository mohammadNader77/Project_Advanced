 `timescale 1ns / 1ps
module Traffic_Light_Controller(


    input clk,rst,go,
    output reg [1:0] highway_signal_1,
    output reg [1:0] highway_signal_2,
    output reg [1:0] farm_signal_1,
    output reg [1:0]farm_signal_2
    );
    
    parameter  S0=0, S1=1, S2 =2, S3=3, S4=4,S5=5,S6=6,S7=7,S8=8,S9=9,S10=10,S11=11,S12=12,S13=13,S14=14,S15=15,S16=16,S17=17;
    reg [7:0]count;
    reg[5:0] ps;
    parameter  sec1=1,sec2=2,sec30=30,sec10=10,sec15=15,sec3=3,sec5=5;

   
    
    always@(posedge clk)
        begin
        if(rst==1)
        begin
        ps<=S0;
        count<=0;
        end
       else if (go) begin
        
      
       
            
            case(ps)
                S0: if(count<sec1)
                        begin
                        ps<=S0;
                        count<=count+1;
                        end
                    else
                        begin
                        ps<=S1;
                        count<=0;
                        end
                S1: if(count<sec2)
                        begin
                        ps<=S1;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S2;
                        count<=0;
                        end
                S2: if(count<sec30)
                        begin
                        ps<=S2;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S3;
                        count<=0;
                        end
                S3:if(count<sec2)
                       begin
                        ps<=S3;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S4;
                        count<=0;
                        end
                S4:if(count<sec10)
                        begin
                        ps<=S4;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S5;
                        count<=0;
                        end

                S5:if(count<sec2)
                        begin
                        ps<=S5;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S6;
                        count<=0;
                        end	   
				S6:if(count<sec1)
                        begin
                        ps<=S6;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S7;
                        count<=0;
                        end
						
						
				 S7:if(count<sec2)
                        begin
                        ps<=S7;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S8;
                        count<=0;
                        end
						
				S8:if(count<sec15)
                        begin
                        ps<=S8;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S9;
                        count<=0;
                        end	
						
						
					S9:if(count<sec2)
                        begin
                        ps<=S9;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S10;
                        count<=0;
                        end	
						
				S10:if(count<sec5)
                        begin
                        ps<=10;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=11;
                        count<=0;
                        end	
						
			 S11:if(count<sec2)
                        begin
                        ps<=S11;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S12;
                        count<=0;
                        end	
				S12:if(count<sec10)
                        begin
                        ps<=S12;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S13;
                        count<=0;
                        end	
						
				 S13:if(count<sec2)
                        begin
                        ps<=S13;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S14;
                        count<=0;
                        end
						
				S14:if(count<sec1)
                        begin
                        ps<=S14;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S15;
                        count<=0;
                        end	
						
				 S15:if(count<sec2)
                        begin
                        ps<=S15;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S16;
                        count<=0;
                        end	
						
				S16:if(count<sec15)
                        begin
                        ps<=S16;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S17;
                        count<=0;
                        end	
						
			 S17:if(count<sec3)
                        begin
                        ps<=S17;
                        count<=count+1;
                        end

                    else
                        begin
                        ps<=S0;
                        count<=0;
                        end	
						
						
						
						
                default: ps<=S0;
                endcase
            end   
			end

            always@(ps)    
            begin
                
                case(ps)
					
					  
					
		
                    S0:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					
					  S1:
                    begin
                       highway_signal_1<=2'b11;
                       highway_signal_2<=2'b11;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S2:
                    begin
                       highway_signal_1<=2'b00;
                       highway_signal_2<=2'b00;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S3:
                    begin
                       highway_signal_1<=2'b00;
                       highway_signal_2<=2'b01;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S4:
                    begin
                       highway_signal_1<=2'b00;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S5:
                    begin
                       highway_signal_1<=2'b01;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S6:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S7:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<=2'b11;
                       farm_signal_2<=2'b11;
                    end	
					  S8:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<=2'b00;
                       farm_signal_2<=2'b00;
                    end	
					  S9:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<=2'b00;
                       farm_signal_2<=2'b01;
                    end	
					  S10:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<=2'b00;
                       farm_signal_2<= 2'b10;
                    end	
					  S11:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<=2'b01;
                       farm_signal_2<=2'b11;
                    end	
					  S12:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<=2'b00;
                    end	
					  S13:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<=2'b01;
                    end	
					  S14:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<= 2'b10;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S15:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<=2'b11;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S16:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<=2'b00;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					  S17:
                    begin
                       highway_signal_1<= 2'b10;
                       highway_signal_2<=2'b01;
                       farm_signal_1<= 2'b10;
                       farm_signal_2<= 2'b10;
                    end	
					default:
                    begin 
                       highway_signal_1<=2'b10;
                       highway_signal_2<=2'b10;
                       farm_signal_1<=2'b10;
                       farm_signal_2<=2'b10;
                    end
					
				
                   
                    endcase
                            
              
			  end
endmodule

module gen (output reg go,rst,clk);
	
	
	initial
		begin
	    clk=0;
		rst=1;
		#10  rst=0;
		#10  rst=1;
		#1000  rst=0;
	end
	  always #5 clk=~clk;
	initial
		begin 
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;	 
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;	
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;	 
	#100 go =1;
	#100 go =0;	 
	#100 go =1;	
	#100 go =0;	
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;
	#100 go =1;
	#100 go =0;	 
	#100 go =1;
	#100 go =0;	 
	#100 go =1;
    end

	 initial
		begin 
	#6000 $finish;
	   end
	endmodule

	module analyser(h1,h2,f1,f2,clk);
	
			input clk;
			input [1:0] h1,h2,f1,f2; 
			integer counter;
			reg [4:0]pos; 
			
			initial	 begin
			 counter=0;
			  end
			
			always @ (negedge clk) begin	
				
				pos=counter;
				{counter} = counter + 1;
				case(pos)	
					
			5'b00000:begin
		
			   if((counter==1)&&(h1==2'b10)&&(h1==2'b10)&&(h2==2'b10)&&(f1==2'b10)&&(f2==2'b10))
			   $display("state 0 ");  end
			 5'b00001: begin 
				 if((counter==2)&&(h1==2'b11)&&(h1==2'b11)&&(h2==2'b10)&&(f1==2'b10)&&(f2==2'b10))								
				$display("state 1 "); end			
			 5'b00010: begin 
				 if((counter==3)&&(h1==2'b00)&&(h1==2'b00)&&(h2==2'b10)&&(f1==2'b10)&&(f2==2'b10))								
				$display("state 2 "); end
	  	     5'b00011: begin 
				 if((counter==4)&&(h1==2'b00)&&(h1==2'b01)&&(h2==2'b10)&&(f1==2'b10)&&(f2==2'b10))								
				$display("state 3 ");end
			 5'b0100: begin 
				 if((counter==5)&&(h1==2'b00)&&(h1==2'b10)&&(h2==2'b10)&&(f1==2'b10)&&(f2==2'b10))								
				$display("state 4 ");end
				 
				endcase
			 end
	
	
	endmodule  

`timescale 1ns / 1ps


module Traffic_Light_Controller_TB;
wire clk,rst,go;
wire [1:0]highway_signal_1;
wire [1:0]highway_signal_2;
wire [1:0]farm_signal_1;
wire [1:0]farm_signal_2; 

gen g(go,rst,clk);
Traffic_Light_Controller dut(.clk(clk) , .rst(rst) ,.go(go), .highway_signal_1(highway_signal_1) , .highway_signal_2(highway_signal_2)  ,.farm_signal_1(farm_signal_1),.farm_signal_2(farm_signal_2)   );
	analyser s(.h1(highway_signal_1),.h2(highway_signal_2),.f1(farm_signal_1),.f2(farm_signal_2),.clk(clk));

endmodule 



	