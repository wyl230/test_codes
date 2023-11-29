
import { Base } from "./base";
import { print } from "./utils";

export class Has {
  constructor(
    public parent: Base
  ) {
    print('Has constructor');
  }
}

// const has = new Has(new Base());
