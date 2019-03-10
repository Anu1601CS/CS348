// author: Anurag

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.math.BigInteger;

public class ObtainSHA {
  public static int SHA1(String message) throws HashGenerationException {
    try {
      MessageDigest digest = MessageDigest.getInstance("SHA-1");
      byte[] hashedBytes = digest.digest(message.getBytes("UTF-8"));
      int key = Integer.parseInt(new BigInteger(convertToHex(hashedBytes), 16).toString(2).substring(1, Peer.m + 1), 2);
      return key;
    } catch (NoSuchAlgorithmException | UnsupportedEncodingException ex) {
        throw new HashGenerationException("Could not generate hash from String", ex);
    }
  }
  private static String convertToHex(byte[] data) {
    StringBuffer buf = new StringBuffer();
    for (int i = 0; i < data.length; i++) {
      int halfbyte = (data[i] >>> 4) & 0x0F;
      int two_halfs = 0;
      do {
        if ((0 <= halfbyte) && (halfbyte <= 9))
          buf.append((char) ('0' + halfbyte));
        else
          buf.append((char) ('a' + (halfbyte - 10)));
        halfbyte = data[i] & 0x0F;
      } while(two_halfs++ < 1);
    }
    return buf.toString();
  }
}
class HashGenerationException extends Exception {
  public HashGenerationException() {
  	super();
  }
  public HashGenerationException(String message, Throwable throwable) {
  	super(message, throwable);
  }
  public HashGenerationException(String message) {
  	super(message);
  }
  public HashGenerationException(Throwable throwable) {
  	super(throwable);
  }
}
