import { print } from './utils'
import { Has } from './has_parent'

export class Base {
  has: Has
  constructor() {
    print('Base constructor')

    this.has = new Has(
      this,
    );
  }
}

