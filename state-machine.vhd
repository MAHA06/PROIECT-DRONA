library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
entity fsm is
	port (clk,rst,start,timer_hover, timer_pitch: in std_logic; height, curr_desired_yaw, desired_yaw: in integer range 0 to 300; state_out: out std_logic_vector(4 downto 0));
end entity;
architecture beh of fsm is
	type state_type is (s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26);
	signal state : state_type;
	signal n1,n2,m: integer range 0 to 10;
	signal desired_yaw_new:integer range 0 to 300; 
	begin
	
	desired_yaw_new <= desired_yaw+1;
	
	process1: process (clk,rst)
		begin
			if (rst ='1') then
				state <=s1;
			elsif (rising_edge(clk)) then
				case state is
					when s1 => if (start='1') then if (height<148) then state<=s2; elsif (height>152) then state<=s3; else state<=s4; end if; else state<=s1; end if; n1<=5; n2<=5; m<=3;
					when s2 => if (height>152) then state<=s3; elsif (height<148) then state<=s2; else state<=s4; end if;
					when s3 => if (height>152) then state<=s3; elsif (height<148) then state<=s2; else state<=s4; end if;
					when s4 => if ((curr_desired_yaw>desired_yaw-1) and (curr_desired_yaw<desired_yaw_new)) then state<=s5; else state<=s4; end if;
					when s5 => if (timer_hover='1') then state<=s6; else state<=s5; end if;
					when s6 => if (timer_pitch='1') then state<=s7; else state<=s6; end if; n1<=n1-1; m<=m-1;
					when s7 => if ((curr_desired_yaw>desired_yaw-1) and (curr_desired_yaw<desired_yaw+1)) then if (height<148) then state<=s8; elsif (height>152) then state<=s9; else state<=s10; end if; else state<=s7; end if;
					when s8 => if (height>152) then state<=s9; elsif (height<148) then state<=s8; else state<=s10; end if; 
					when s9 => if (height>152) then state<=s9; elsif (height<148) then state<=s8; else state<=s10; end if;
					when s10 => if ((timer_hover='1') and (n1=0)) then state<=s11; elsif ((n1=0)) then state<=s10; else state<=s6; end if;
					when s11 => if ((curr_desired_yaw>desired_yaw+89) and (curr_desired_yaw<desired_yaw+91)) then state<=s12; else state<=s11; end if;
					when s12 => if (timer_pitch='1') then state<=s13; else state<=s12; end if;
					when s13 => if ((curr_desired_yaw>desired_yaw+179) and (curr_desired_yaw<desired_yaw+181)) then if (height<148) then state<=s14; elsif (height>152) then state<=s15; else state<=s16; end if; else state<=s13; end if;
					when s14 => if (height>152) then state<=s15; elsif (height<148) then state<=s14; else state<=s16; end if;
					when s15 => if (height>152) then state<=s15; elsif (height<148) then state<=s14; else state<=s16; end if;
					when s16 => if (timer_hover='1') then state<=s17; else state<=s16; end if;
					when s17 => if (timer_pitch='1') then state<=s18; else state<=s17; end if; n2<=n2-1;
					when s18 => if ((curr_desired_yaw>desired_yaw+179) and (curr_desired_yaw<desired_yaw+181)) then if (height<148) then state<=s19; elsif (height>152) then state<=s20; else state<=s21; end if; else state<=s18; end if;
					when s19 => if (height>152) then state<=s20; elsif (height<148) then state<=s19; else state<=s21; end if; 
					when s20 => if (height>152) then state<=s20; elsif (height<148) then state<=s19; else state<=s21; end if; 
					when s21 => if ((timer_hover='1') and (n2=0)) then state<=s22; elsif ((n2=0)) then state<=s21; else state<=s17; end if;
					when s22 => if ((curr_desired_yaw>desired_yaw+89) and (curr_desired_yaw<desired_yaw+91)) then state<=s23; else state<=s22; end if;
					when s23 => if (timer_pitch='1') then state<=s24; else state<=s23; end if;
					when s24 => if ((curr_desired_yaw>desired_yaw-1) and (curr_desired_yaw<desired_yaw+1)) then state<=s25; else state<=s24; end if;
					when s25 => if ((timer_hover='1') and (m=0)) then state<=s26; elsif ((n2=0)) then state<=s25; else state<=s6; end if;
					when s26 => state<=s26;
				end case;
			end if;
	end process process1;
	process2: process (state)
	begin
		case state is
			when s1 => state_out<="00000";	--standby
			when s2 => state_out<="00001";	--autolevel +
			when s3 => state_out<="00010";	--autolevel -
			when s4 => state_out<="00011";	--set desired_yaw
			when s5 => state_out<="00100";	--hover
			when s6 => state_out<="00101"; 	--pitch
			when s7 => state_out<="00110";	--set desired_yaw
			when s8 => state_out<="00111"; 	--autolevel +
			when s9 => state_out<="01000"; 	--autolevel -
			when s10 => state_out<="01001"; --hover
			when s11 => state_out<="01010"; --set desired_yaw +90
			when s12 => state_out<="01011"; --pitch
			when s13 => state_out<="01100"; --set desired_yaw +180
			when s14 => state_out<="01101"; --autolevel +
			when s15 => state_out<="01110"; --autolevel -
			when s16 => state_out<="01111"; --hover
			when s17 => state_out<="10000"; --pitch
			when s18 => state_out<="10001"; --set desired_yaw +180
			when s19 => state_out<="10010"; --autolevel +
			when s20 => state_out<="10011"; --autolevel -
			when s21 => state_out<="10100"; --hover
			when s22 => state_out<="10100"; --set desired_yaw +90
			when s23 => state_out<="10101"; --pitch
			when s24 => state_out<="10110"; --set desired_yaw
			when s25 => state_out<="10111"; --hover
			when s26 => state_out<="11000"; --done
		end case;
	end process process2;
end beh; 