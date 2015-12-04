#include "_tempdir.bash"

cat > test.v <<EOF
module euclid(m_in, n_in, gcd, clk, rst);
  input  [15:0] m_in;
  input  [15:0] n_in;
  output [15:0] gcd;
  reg    [15:0] gcd;
  input  clk;
  input  rst;

  reg [15:0] m, m_next;
  reg [15:0] n, n_next;
  reg done, done_next;
  reg [15:0] factor, factor_next;
  reg [1:0] state, state_next;

  parameter s0 = 2'd0, s1 = 2'd1, s2 = 2'd2;

  always @(posedge clk)
   if (rst) begin
     n      <= 16'd0;
     m      <= 16'd0;
     done   <= 1'd0;
     factor <= 16'd0;
     state  <= s0;
   end else begin
     n      <= n_next;
     m      <= m_next;
     done   <= done_next;
     factor <= factor_next;
     state  <= state_next;
   end

  always @(*) begin
    n_next      <= n;       // default reg assignment
    m_next      <= m;       // default reg assignment
    done_next   <= done;    // default reg assignment
    factor_next <= factor;  // default reg assignment
    gcd         <= 16'd0;   // default output assignment

    case (state)

      s0: begin
          m_next      <= m_in;
          n_next      <= n_in;
          factor_next <= 16'd0;
          done_next   <= 1'd0;
          gcd         <= 16'd0;
          state_next <= s1;
          end

      s1: if (done) begin
             gcd <= ((m > n) ? m : n) << factor;
             state_next <= s2;
          end else if (m[0] & n[0]) begin
             m_next    <= (m >= n) ? m - n : m;
             n_next    <= (n >  m) ? n - m : n;
             gcd       <= 16'd0;
             done_next <= ((m == 0) | (n == 0));
             state_next <= s1;
          end else if (m[0] & ~n[0]) begin
             n_next <= n >> 1;
             gcd       <= 16'd0;
             done_next <= ((m == 0) | (n == 0));
             state_next <= s1;
          end else if (~m[0] & n[0]) begin
             m_next <= m >> 1;
             gcd       <= 16'd0;
             done_next <= ((m == 0) | (n == 0));
             state_next <= s1;
          end else begin
             n_next <= n >> 1;
             m_next <= m >> 1;
             factor_next <= factor + 1;
             gcd       <= 16'd0;
             done_next <= ((m == 0) | (n == 0));
             state_next <= s1;
          end

      s2: begin
          gcd       <= 16'd0;
          done_next <= ((m == 0) | (n == 0));
          state_next<= s2;
          end

      default: begin
               state_next <= s0;  // jump back to init
               end
    endcase
  end

endmodule
EOF

#include "_harness.bash"
